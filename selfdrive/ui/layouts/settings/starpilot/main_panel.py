from __future__ import annotations
from collections.abc import Callable
import pyray as rl

from openpilot.common.params import Params
from openpilot.system.ui.widgets import Widget
from openpilot.system.ui.lib.multilang import tr, tr_noop
from openpilot.system.ui.lib.application import MousePos, gui_app, FontWeight

from openpilot.selfdrive.ui.layouts.settings.starpilot.panel import StarPilotPanelType, StarPilotPanelInfo
from openpilot.selfdrive.ui.layouts.settings.starpilot.sounds import StarPilotSoundsLayout
from openpilot.selfdrive.ui.layouts.settings.starpilot.driving_model import StarPilotDrivingModelLayout
from openpilot.selfdrive.ui.layouts.settings.starpilot.longitudinal import StarPilotLongitudinalLayout
from openpilot.selfdrive.ui.layouts.settings.starpilot.lateral import StarPilotLateralLayout
from openpilot.selfdrive.ui.layouts.settings.starpilot.maps import StarPilotMapsLayout
from openpilot.selfdrive.ui.layouts.settings.starpilot.system_settings import StarPilotSystemLayout
from openpilot.selfdrive.ui.layouts.settings.starpilot.appearance import StarPilotAppearanceLayout
from openpilot.selfdrive.ui.layouts.settings.starpilot.vehicle import StarPilotVehicleSettingsLayout

from openpilot.selfdrive.ui.layouts.settings.starpilot.aethergrid import TileGrid, HubTile, RadioTileGroup, SPACING

class StarPilotLayout(Widget):
  CATEGORIES = [
    {
      "title": "Sounds & Alerts",
      "icon": "sound",
      "panel": "SOUNDS",
    },
    {
      "title": "Driving Controls",
      "icon": "steering",
      "buttons": [("DRIVING MODEL", "DRIVING_MODEL", "aicar"), ("GAS / BRAKE", "LONGITUDINAL", "road"), ("STEERING", "LATERAL", "steering")],
    },
    {
      "title": "Map Data",
      "icon": "navigate",
      "panel": "MAPS",
    },
    {
      "title": "System",
      "icon": "system",
      "panel": "SYSTEM",
    },
    {
      "title": "Appearance",
      "icon": "display",
      "panel": "VISUALS",
    },
    {
      "title": "Vehicle Settings",
      "icon": "vehicle",
      "panel": "VEHICLE",
    },
  ]

  def __init__(self):
    super().__init__()
    self._params = Params()

    self._current_panel = StarPilotPanelType.MAIN
    self._current_category_idx: int | None = None
    self._depth_callback: Callable | None = None
    self._settings_layout = None

    StarPilotLayout.active_instance = self

    self._panel_stack: list[tuple[StarPilotPanelType, str]] = []
    self._sub_panel_callbacks: dict[str, Callable] = {}

    self._panels = {
      StarPilotPanelType.MAIN: StarPilotPanelInfo("", None),
      StarPilotPanelType.SOUNDS: StarPilotPanelInfo(tr_noop("Sounds"), StarPilotSoundsLayout()),
      StarPilotPanelType.SYSTEM: StarPilotPanelInfo(tr_noop("System Settings"), StarPilotSystemLayout()),
      StarPilotPanelType.DRIVING_MODEL: StarPilotPanelInfo(tr_noop("Driving Model"), StarPilotDrivingModelLayout()),
      StarPilotPanelType.LONGITUDINAL: StarPilotPanelInfo(tr_noop("Gas / Brake"), StarPilotLongitudinalLayout()),
      StarPilotPanelType.LATERAL: StarPilotPanelInfo(tr_noop("Steering"), StarPilotLateralLayout()),
      StarPilotPanelType.MAPS: StarPilotPanelInfo(tr_noop("Map Data"), StarPilotMapsLayout()),
      StarPilotPanelType.VISUALS: StarPilotPanelInfo(tr_noop("Appearance"), StarPilotAppearanceLayout()),
      StarPilotPanelType.VEHICLE: StarPilotPanelInfo(tr_noop("Vehicle Settings"), StarPilotVehicleSettingsLayout()),
    }

    self._setup_sub_panels(
      StarPilotPanelType.LONGITUDINAL,
      StarPilotPanelType.SOUNDS,
      StarPilotPanelType.SYSTEM,
      StarPilotPanelType.LATERAL,
      StarPilotPanelType.MAPS,
      StarPilotPanelType.VISUALS,
      StarPilotPanelType.VEHICLE,
    )

    self._main_grid = TileGrid(columns=None, padding=SPACING.tile_gap)
    self._rebuild_grid()

  def set_depth_callback(self, callback: Callable):
    self._depth_callback = callback

  def set_settings_layout(self, settings_layout):
    self._settings_layout = settings_layout

  def navigate_back(self):
    if self._panel_stack:
      self._panel_stack.pop()
      self._update_sub_panel_visibility()
      self._update_depth()
    elif self._current_panel != StarPilotPanelType.MAIN:
      if self._current_category_idx is not None:
        cat_info = self.CATEGORIES[self._current_category_idx]
        if "buttons" in cat_info:
          self._set_current_panel(StarPilotPanelType.MAIN)
        else:
          self._current_category_idx = None
          self._set_current_panel(StarPilotPanelType.MAIN)
      else:
        self._set_current_panel(StarPilotPanelType.MAIN)
    elif self._current_category_idx is not None:
      self._current_category_idx = None
      self._rebuild_grid()
      if self._depth_callback:
        self._depth_callback(0)

  def _update_depth(self):
    depth = 0
    if self._current_panel != StarPilotPanelType.MAIN:
      if self._current_category_idx is not None:
        cat_info = self.CATEGORIES[self._current_category_idx]
        depth = 2 if "buttons" in cat_info else 1
      else:
        depth = 1
      # Deep nesting check
      if self._panel_stack:
        depth += len(self._panel_stack)
    elif self._current_category_idx is not None:
      depth = 1

    if self._depth_callback:
      self._depth_callback(depth)

  def _push_sub_panel(self, sub_panel_name: str):
    if sub_panel_name:
      self._panel_stack.append((self._current_panel, sub_panel_name))
    else:
      while self._panel_stack and self._panel_stack[-1][0] == self._current_panel:
        self._panel_stack.pop()
    self._update_sub_panel_visibility()
    self._update_depth()

  def _update_sub_panel_visibility(self):
    panel = self._panels[self._current_panel].instance
    current_sub = self._get_current_sub_panel()
    if panel and hasattr(panel, 'set_current_sub_panel'):
      panel.set_current_sub_panel(current_sub)

  def _get_current_sub_panel(self) -> str:
    if self._panel_stack and self._panel_stack[-1][0] == self._current_panel:
      return self._panel_stack[-1][1]
    return ""

  def _setup_sub_panels(self, *panel_types: StarPilotPanelType):
    for panel_type in panel_types:
      panel = self._panels[panel_type].instance
      if panel and hasattr(panel, 'set_navigate_callback'):
        panel.set_navigate_callback(self._push_sub_panel)

  def _rebuild_grid(self):
    self._main_grid.clear()

    panel_type_map = {
      "SOUNDS": StarPilotPanelType.SOUNDS,
      "SYSTEM": StarPilotPanelType.SYSTEM,
      "DRIVING_MODEL": StarPilotPanelType.DRIVING_MODEL,
      "LONGITUDINAL": StarPilotPanelType.LONGITUDINAL,
      "LATERAL": StarPilotPanelType.LATERAL,
      "MAPS": StarPilotPanelType.MAPS,
      "VISUALS": StarPilotPanelType.VISUALS,
      "VEHICLE": StarPilotPanelType.VEHICLE,
    }

    if self._current_category_idx is None:
      # Main Categories Grid
      for i, cat in enumerate(self.CATEGORIES):
        def on_click(idx=i):
          cat_info = self.CATEGORIES[idx]
          self._current_category_idx = idx
          panel_key = cat_info.get("panel")
          if panel_key is not None:
            self._set_current_panel(panel_type_map[panel_key])
          else:
            self._rebuild_grid()
            if self._depth_callback:
              self._depth_callback(1)

        tile = HubTile(
          title=tr(cat["title"]),
          desc=tr(cat.get("desc", "")),
          icon_key=cat["icon"],
          on_click=on_click,
          bg_color=cat.get("color")
        )
        self._main_grid.add_tile(tile)
    else:
      # Sub-buttons Grid for selected Category
      cat = self.CATEGORIES[self._current_category_idx]
      visible_buttons = cat["buttons"]

      for button_info in visible_buttons:
        if len(button_info) == 3:
          label, panel_key, btn_icon = button_info
        else:
          label, panel_key = button_info
          btn_icon = cat["icon"]

        p_type = panel_type_map[panel_key]
        def on_btn_click(p=p_type):
          self._set_current_panel(p)

        tile = HubTile(
          title=tr(label),
          desc="",
          icon_key=btn_icon,
          on_click=on_btn_click,
          bg_color=cat.get("color")
        )
        self._main_grid.add_tile(tile)

  def _set_current_panel(self, panel_type: StarPilotPanelType):
    if panel_type != self._current_panel:
      if self._current_panel != StarPilotPanelType.MAIN:
        self._panels[self._current_panel].instance.hide_event()
      self._current_panel = panel_type
      if panel_type != StarPilotPanelType.MAIN:
        self._panels[panel_type].instance.show_event()
      else:
        self._rebuild_grid()

    self._update_depth()

  def _render(self, rect: rl.Rectangle):
    import openpilot.selfdrive.ui.layouts.settings.starpilot.aethergrid as aethergrid
    metrics = aethergrid.AETHER_LIST_METRICS

    TOP_BAR_HEIGHT = 80
    content_rect = rl.Rectangle(rect.x, rect.y + TOP_BAR_HEIGHT, rect.width, rect.height - TOP_BAR_HEIGHT)

    # Standardize width to perfectly match subpanel shells
    shell_w = min(rect.width - metrics.outer_margin_x * 2, metrics.max_content_width)
    shell_x = rect.x + (rect.width - shell_w) / 2

    # 0. Draw Tinted Cockpit Glass Background as a floating, rounded panel
    glass_rect = rl.Rectangle(shell_x, rect.y + 18, shell_w, TOP_BAR_HEIGHT - 24)
    aethergrid._draw_rounded_fill(glass_rect, rl.Color(18, 16, 24, 180), radius_px=16)
    aethergrid._draw_rounded_stroke(glass_rect, rl.Color(255, 255, 255, 20), radius_px=16)

    # 1. Draw breadcrumbs in top bar — pass the full pill rect for proper vertical centering
    # Reserve space on the right for the badge + time (estimated ~260px)
    crumb_rect = rl.Rectangle(glass_rect.x, glass_rect.y, glass_rect.width - 260, glass_rect.height)
    aethergrid.draw_breadcrumbs(crumb_rect)

    # 2. Draw Time/Clock on right
    import time
    from openpilot.system.ui.lib.text_measure import measure_text_cached
    current_time = time.strftime("%I:%M %p").lstrip("0")
    font = gui_app.font(FontWeight.SEMI_BOLD)
    font_size = 28
    time_w = measure_text_cached(font, current_time, font_size).x
    time_x = glass_rect.x + glass_rect.width - time_w - 20
    time_y = glass_rect.y + (glass_rect.height - 28) / 2
    rl.draw_text_ex(font, current_time, rl.Vector2(time_x, time_y), font_size, 0, rl.Color(160, 170, 185, 255))

    # 3. Draw Network/Wifi Badge
    from openpilot.selfdrive.ui.ui_state import ui_state
    network_type = ui_state.sm["deviceState"].networkType if ui_state.sm.valid.get("deviceState", False) else 0
    if network_type == 1:
      network_str = "WIFI"
      network_color = rl.Color(34, 197, 94, 255)
    elif network_type in (2, 3, 4, 5):
      network_str = "CELL"
      network_color = rl.Color(59, 130, 246, 255)
    else:
      network_str = "OFFLINE"
      network_color = rl.Color(239, 68, 68, 255)

    badge_w = measure_text_cached(font, network_str, 20).x + 24
    badge_rect = rl.Rectangle(time_x - badge_w - 20, glass_rect.y + (glass_rect.height - 32) / 2, badge_w, 32)
    rl.draw_rectangle_rounded(badge_rect, 0.35, 8, rl.Color(network_color.r, network_color.g, network_color.b, 24))
    rl.draw_rectangle_rounded_lines_ex(badge_rect, 0.35, 8, 1.5, rl.Color(network_color.r, network_color.g, network_color.b, 70))
    badge_text_pos = rl.Vector2(badge_rect.x + 12, badge_rect.y + 6)
    rl.draw_text_ex(font, network_str, badge_text_pos, 20, 0, network_color)

    # 5. Render active content panel
    if self._current_panel == StarPilotPanelType.MAIN:
      grid_rect = rl.Rectangle(shell_x, content_rect.y + metrics.outer_margin_y, shell_w, content_rect.height - metrics.outer_margin_y * 2)
      self._main_grid.render(grid_rect)
    else:
      panel = self._panels[self._current_panel]
      if panel.instance:
        panel.instance.render(content_rect)

  def _handle_mouse_press(self, mouse_pos: MousePos):
    import openpilot.selfdrive.ui.layouts.settings.starpilot.aethergrid as aethergrid
    aethergrid.PRESSED_BREADCRUMB = aethergrid.resolve_interactive_target(mouse_pos, aethergrid.BREADCRUMB_RECTS, None, pad_x=12, pad_y=12)

  def _handle_mouse_release(self, mouse_pos: MousePos):
    import openpilot.selfdrive.ui.layouts.settings.starpilot.aethergrid as aethergrid
    target = aethergrid.resolve_interactive_target(mouse_pos, aethergrid.BREADCRUMB_RECTS, None, pad_x=12, pad_y=12)
    if target and target == aethergrid.PRESSED_BREADCRUMB:
      aethergrid.handle_breadcrumb_click(target)
    aethergrid.PRESSED_BREADCRUMB = None

  def _handle_mouse_event(self, mouse_event):
    pass


  def show_event(self):
    super().show_event()
    if self._current_panel != StarPilotPanelType.MAIN:
      self._panels[self._current_panel].instance.show_event()

  def hide_event(self):
    super().hide_event()
    if self._current_panel != StarPilotPanelType.MAIN:
      self._panels[self._current_panel].instance.hide_event()
