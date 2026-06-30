from __future__ import annotations

import pyray as rl

from openpilot.system.hardware import HARDWARE
from openpilot.selfdrive.ui.lib.starpilot_state import starpilot_state
from openpilot.system.ui.lib.application import gui_app, FontWeight
from openpilot.system.ui.lib.multilang import tr
from openpilot.system.ui.widgets import DialogResult
from openpilot.system.ui.widgets.confirm_dialog import ConfirmDialog

from openpilot.selfdrive.ui.layouts.settings.starpilot.panel import _SettingsPage
from openpilot.selfdrive.ui.layouts.settings.starpilot.aethergrid import (
  AetherAdjustorRow,
  AetherListMetrics,
  AetherSliderDialog,
  DEFAULT_PANEL_STYLE,
  PanelManagerView,
  TileGrid,
  draw_list_group_shell,
  draw_section_header,
  draw_settings_list_row,
  SECTION_GAP,
  SECTION_HEADER_HEIGHT,
  SECTION_HEADER_GAP,
)


def _confirm_reboot_toggle(params, key, state):
  params.put_bool(key, state)
  from openpilot.selfdrive.ui.ui_state import ui_state
  if ui_state.started:
    gui_app.push_widget(ConfirmDialog(
      tr("Reboot required. Reboot now?"), tr("Reboot"), tr("Cancel"),
      callback=lambda res: HARDWARE.reboot() if res == DialogResult.CONFIRM else None,
    ))


CUSTOM_METRICS = AetherListMetrics(
  max_content_width=1560,
  outer_margin_x=18,
  outer_margin_y=10,
  panel_padding_x=16,
  panel_padding_top=16,
  panel_padding_bottom=12,
  header_height=0,
  section_gap=12,
  section_header_height=28,
  section_header_gap=8,
  row_height=104,
  utility_row_height=88,
)

PANEL_STYLE = DEFAULT_PANEL_STYLE
ALT_ROW_HEIGHT = 88.0

_LATERAL_TUNE_KEYS = ["TurnDesires", "NNFF", "NNFFLite", "ForceTorqueController"]
_ADVANCED_LATERAL_KEYS = ["ForceAutoTune", "ForceAutoTuneOff"]


def _sync_parent(params, parent_key, child_keys):
  if any(params.get_bool(k) for k in child_keys):
    if not params.get_bool(parent_key):
      params.put_bool(parent_key, True)
  else:
    if params.get_bool(parent_key):
      params.put_bool(parent_key, False)


# ═══════════════════════════════════════════════════════════════
# SteeringSubPanelView — two-column sub-panel
# ═══════════════════════════════════════════════════════════════

class SteeringSubPanelView(PanelManagerView):
  """Two-column sub-panel: left = AetherAdjustorRows (values),
     right = TileGrid of ToggleTile (toggles).
     Dynamic visibility via _rebuild_content()."""

  METRICS = CUSTOM_METRICS

  @property
  def vertical_scrolling_disabled(self) -> bool:
    return True

  def __init__(self, controller, header_title, header_subtitle,
               adjustor_defs, toggle_defs, include_alt_row=False):
    super().__init__()
    self._controller = controller
    self._header_title = header_title
    self._header_subtitle = header_subtitle
    self._adjustor_defs = adjustor_defs
    self._toggle_defs = toggle_defs
    self._include_alt_row = include_alt_row
    self._adjustor_rows: dict[str, AetherAdjustorRow] = {}
    self._left_container_h = 0.0
    self._tiles_container_h = 0.0

    self._toggle_grid = TileGrid(
      columns=2, padding=12, force_square=True,
      min_tile_height=130.0, max_tile_height=280.0,
    )
    self.register_page_grid(self._toggle_grid)

    self._rebuild_content()

  def _render(self, rect: rl.Rectangle):
    self._rebuild_adjustors()
    super()._render(rect)

  def _rebuild_content(self):
    self._rebuild_adjustors()
    self._rebuild_toggle_pages()

  def _rebuild_adjustors(self):
    old_rows = self._adjustor_rows
    self._adjustor_rows = {}

    for defn in self._adjustor_defs:
      if defn.get("visible") is not None and not defn["visible"]():
        continue
      key = defn["key"]
      if key in old_rows:
        self._adjustor_rows[key] = old_rows[key]
      else:
        self._adjustor_rows[key] = AetherAdjustorRow(
          tr(defn["title"]),
          tr(defn.get("subtitle", "")),
          defn["min_val"], defn["max_val"], defn["step"],
          get_value=lambda k=key: self._controller._params.get_float(k),
          on_change=lambda _v: None,
          on_commit=None,
          unit=defn.get("unit", ""),
          labels=defn.get("labels"),
          presets=defn.get("presets", []),
          is_active=lambda: False,
          set_active=lambda active, k=key: self._show_slider_for(k) if active else None,
          style=PANEL_STYLE,
          color=PANEL_STYLE.accent,
        )

  def _rebuild_toggle_pages(self):
    visible = [
      d for d in self._toggle_defs
      if d.get("visible") is None or d["visible"]()
    ]
    wrapped = []
    for d in visible:
      entry = dict(d)
      original_set = entry.get("set")
      if original_set:
        def make_wrapped(orig):
          def fn(state):
            orig(state)
            self._rebuild_content()
          return fn
        entry["set"] = make_wrapped(original_set)
      wrapped.append(entry)
    pages = [wrapped[i:i+4] for i in range(0, len(wrapped), 4)]
    old_page = self._current_page
    self._toggle_pages = pages
    self._page_count = max(1, len(pages))
    self._current_page = min(old_page, self._page_count - 1)
    self._on_page_changed()

  def _show_slider_for(self, key: str):
    self._controller._on_select(key)

  def show_event(self):
    super().show_event()
    starpilot_state.update(force=True)
    self._rebuild_content()

  # ── layout / rendering ──

  def _draw_header(self, rect):
    pass

  def _measure_content_height(self, content_width: float) -> float:
    col_width = (content_width - SECTION_GAP) / 2

    for row in self._adjustor_rows.values():
      row.custom_row_height = None

    header_h = self._header_height()
    left_natural = sum(row.measure_height(col_width) for row in self._adjustor_rows.values())
    left_natural += 16.0

    tiles_needed_h = self.measure_page_grid_height(self._toggle_grid, col_width - 24) + 24
    max_natural_h = max(left_natural, tiles_needed_h)
    section_overhead = SECTION_HEADER_HEIGHT + SECTION_HEADER_GAP

    alt_consumption = (ALT_ROW_HEIGHT + 12.0) if self._include_alt_row else 0.0

    if self._scroll_rect:
      available_h = self._scroll_rect.height - header_h - section_overhead - 6.0 - alt_consumption
    else:
      available_h = max_natural_h

    max_container_h = max(0.0, available_h)

    left_available = max_container_h - 16.0
    if self._adjustor_rows and left_available > 0:
      row_h = max(60.0, left_available / len(self._adjustor_rows))
      for row in self._adjustor_rows.values():
        row.custom_row_height = row_h

    self._left_container_h = max_container_h
    self._tiles_container_h = max_container_h

    return self._compute_two_column_height(header_h + section_overhead + max_container_h + alt_consumption)

  def _header_height(self) -> float:
    h = 0.0
    if self._header_title:
      h += 30 + 6
      if self._header_subtitle:
        h += 22 + 4
    return h

  def _draw_scroll_content(self, rect: rl.Rectangle, content_width: float):
    y = rect.y + self._scroll_offset

    # Draw panel title + subtitle
    if self._header_title:
      rl.draw_text_ex(
        gui_app.font(FontWeight.SEMI_BOLD), self._header_title,
        rl.Vector2(rect.x + 8, y), 30, 0, PANEL_STYLE.title_color,
      )
      y += 30 + 6
      if self._header_subtitle:
        rl.draw_text_ex(
          gui_app.font(FontWeight.NORMAL), self._header_subtitle,
          rl.Vector2(rect.x + 8, y), 22, 0, PANEL_STYLE.subtitle_color,
        )
        y += 22 + 4
    else:
      y += 8

    col_width = (content_width - SECTION_GAP) / 2

    draw_section_header(
      rl.Rectangle(rect.x, y, col_width, SECTION_HEADER_HEIGHT),
      tr("Values"), style=PANEL_STYLE,
    )
    draw_section_header(
      rl.Rectangle(rect.x + col_width + SECTION_GAP, y, col_width, SECTION_HEADER_HEIGHT),
      tr("Toggles"), style=PANEL_STYLE,
    )
    y += SECTION_HEADER_HEIGHT + SECTION_HEADER_GAP

    self._draw_adjustor_column(y, rect.x, col_width)
    self._draw_two_column_tile_grid(
      self._toggle_grid,
      rect.x + col_width + SECTION_GAP, y, col_width,
      self._tiles_container_h, title=None, style=PANEL_STYLE,
    )

    if self._include_alt_row:
      alt_y = y + self._tiles_container_h + 12.0
      alt_rect = rl.Rectangle(rect.x, alt_y, content_width, ALT_ROW_HEIGHT)
      alt_state = self._controller._params.get_bool("AdvancedLateralTune")
      alt_value = tr("ON") if alt_state else tr("OFF")
      hovered, pressed = self._interactive_state("static:alt_row", alt_rect)
      draw_settings_list_row(
        alt_rect,
        title=tr("Advanced Lateral Tuning"),
        value=alt_value,
        enabled=True,
        hovered=hovered,
        pressed=pressed,
        is_last=False,
        show_chevron=True,
        title_size=30,
        subtitle_size=20,
        value_size=24,
        style=PANEL_STYLE,
      )

  def _draw_adjustor_column(self, y: float, x: float, width: float):
    draw_list_group_shell(
      rl.Rectangle(x, y, width, self._left_container_h),
      style=PANEL_STYLE,
    )
    current_y = y + 8
    for key, adjustor in self._adjustor_rows.items():
      row_h = adjustor.measure_height(width)
      row_rect = rl.Rectangle(x, current_y, width, row_h)
      adjustor.set_parent_rect(self._scroll_rect)
      adjustor.render(row_rect)
      current_y += row_h

  # ── mouse forwarding ──

  def _handle_mouse_press(self, mouse_pos):
    super()._handle_mouse_press(mouse_pos)
    for adjustor in self._adjustor_rows.values():
      adjustor._handle_mouse_press(mouse_pos)
    self._toggle_grid._handle_mouse_press(mouse_pos)

  def _handle_mouse_release(self, mouse_pos):
    for adjustor in self._adjustor_rows.values():
      adjustor._handle_mouse_release(mouse_pos)
    self._toggle_grid._handle_mouse_release(mouse_pos)
    super()._handle_mouse_release(mouse_pos)

  def _handle_mouse_event(self, mouse_event):
    super()._handle_mouse_event(mouse_event)
    for adjustor in self._adjustor_rows.values():
      adjustor._handle_mouse_event(mouse_event)
    self._toggle_grid._handle_mouse_event(mouse_event)

  def _activate_target(self, target_id: str | None):
    if target_id == "static:alt_row":
      self._controller._navigate_to("tuning")
      return
    super()._activate_target(target_id)


# ═══════════════════════════════════════════════════════════════
# StarPilotLateralLayout — controller
# ═══════════════════════════════════════════════════════════════

class StarPilotLateralLayout(_SettingsPage):

  def __init__(self):
    super().__init__()
    self._build_panels()

  def _build_panels(self):
    p = self._params
    cs = starpilot_state.car_state

    def alt_on():
      return p.get_bool("AdvancedLateralTune")

    def aol_on():
      return p.get_bool("AlwaysOnLateral")

    def lc_on():
      return p.get_bool("LaneChanges")

    def nlc_on():
      return lc_on() and p.get_bool("NudgelessLaneChange")

    def pos_on():
      return p.get_bool("PauseLateralOnSignal")

    # ── Steering Behavior ──

    sb_adjustors = [
      {
        "key": "PauseAOLOnBrake",
        "title": tr("Pause AOL On Brake"),
        "subtitle": tr("Pause AOL below this speed while brake is pressed."),
        "min_val": 0, "max_val": 100, "step": 1,
        "unit": " mph",
        "visible": aol_on,
      },
      {
        "key": "PauseLateralSpeed",
        "title": tr("Pause Lateral Below"),
        "subtitle": tr("Pause steering below the set speed."),
        "min_val": 0, "max_val": 100, "step": 1,
        "unit": " mph",
      },
      {
        "key": "LateralResumeDelay",
        "title": tr("Resume Delay"),
        "subtitle": tr("Delay before lateral resumes after signal off. 0 = Off."),
        "min_val": 0.0, "max_val": 5.0, "step": 0.1,
        "unit": "s",
        "labels": {0.0: tr("Off")},
        "visible": pos_on,
      },
    ]

    sb_toggles = [
      {
        "title": tr("Always On Lateral"),
        "subtitle": tr("Steering stays active when ACC is off."),
        "get": lambda: p.get_bool("AlwaysOnLateral"),
        "set": lambda s: _confirm_reboot_toggle(p, "AlwaysOnLateral", s) if s else p.put_bool("AlwaysOnLateral", False),
      },
      {
        "title": tr("Turn Signal Only"),
        "subtitle": tr("Only pause steering when turn signal is active."),
        "get": lambda: p.get_bool("PauseLateralOnSignal"),
        "set": lambda s: p.put_bool("PauseLateralOnSignal", s),
      },
      {
        "title": tr("Use Route Desires"),
        "subtitle": tr("Allow navigation to request lane keep and turns."),
        "get": lambda: p.get_bool("NavDesiresAllowed"),
        "set": lambda s: p.put_bool("NavDesiresAllowed", s),
      },
    ]

    # ── Lane Changes ──

    lc_adjustors = [
      {
        "key": "MinimumLaneChangeSpeed",
        "title": tr("Min Lane Change Speed"),
        "subtitle": tr("Lowest speed at which openpilot will change lanes."),
        "min_val": 0, "max_val": 100, "step": 1,
        "unit": " mph",
        "visible": lc_on,
      },
      {
        "key": "LaneChangeTime",
        "title": tr("Lane Change Delay"),
        "subtitle": tr("Delay before the start of an automatic lane change. 0 = Instant."),
        "min_val": 0.0, "max_val": 5.0, "step": 0.1,
        "unit": "s",
        "labels": {0.0: tr("Instant")},
        "visible": nlc_on,
      },
      {
        "key": "LaneDetectionWidth",
        "title": tr("Min Lane Width"),
        "subtitle": tr("Prevent lane changes into narrower lanes."),
        "min_val": 0.0, "max_val": 15.0, "step": 0.1,
        "unit": " ft",
        "visible": nlc_on,
      },
      {
        "key": "LaneChangeSmoothing",
        "title": tr("Lane Change Smoothing"),
        "subtitle": tr("Smoothness of lane change commit. 10 = Stock, 1 = Smoothest."),
        "min_val": 1, "max_val": 10, "step": 1,
        "labels": {10.0: tr("Stock")},
        "visible": lc_on,
      },
    ]

    lc_toggles = [
      {
        "title": tr("Lane Changes"),
        "subtitle": tr("Allow openpilot to change lanes."),
        "get": lambda: p.get_bool("LaneChanges"),
        "set": lambda s: p.put_bool("LaneChanges", s),
      },
      {
        "title": tr("Auto Lane Changes"),
        "subtitle": tr("Signal triggers automatic lane change."),
        "get": lambda: p.get_bool("NudgelessLaneChange"),
        "set": lambda s: p.put_bool("NudgelessLaneChange", s),
        "visible": lc_on,
      },
      {
        "title": tr("One Per Signal"),
        "subtitle": tr("One lane change per signal activation."),
        "get": lambda: p.get_bool("OneLaneChange"),
        "set": lambda s: p.put_bool("OneLaneChange", s),
        "visible": nlc_on,
      },
    ]

    # Combined main panel: Steering Behavior + Lane Changes + ALT drill-down
    merged_adjustors = sb_adjustors + lc_adjustors
    merged_toggles = sb_toggles + lc_toggles

    self._manager_view = SteeringSubPanelView(
      self,
      tr("Steering"),
      tr("Configure steering behavior and lane changes."),
      merged_adjustors, merged_toggles,
      include_alt_row=True,
    )

    # ── Advanced Lateral Tuning (sub-panel, accessed via ALT row) ──

    tuning_adjustors = [
      {
        "key": "SteerDelay",
        "title": tr("Actuator Delay"),
        "subtitle": tr("Time between steering command and vehicle response."),
        "min_val": 0.01, "max_val": 1.0, "step": 0.01,
        "unit": "s",
        "visible": lambda: alt_on() and cs.steerActuatorDelay != 0,
      },
      {
        "key": "SteerFriction",
        "title": tr("Friction"),
        "subtitle": tr("Compensates for steering friction around center."),
        "min_val": 0.0, "max_val": max(1.0, cs.friction * 1.5), "step": 0.01,
        "visible": lambda: alt_on() and cs.friction != 0,
      },
      {
        "key": "SteerKP",
        "title": tr("Kp Factor"),
        "subtitle": tr("How strongly openpilot corrects lateral position."),
        "min_val": max(0.01, cs.steerKp) * 0.5, "max_val": max(0.01, cs.steerKp) * 1.5, "step": 0.01,
        "visible": lambda: alt_on() and cs.steerKp != 0,
      },
      {
        "key": "SteerLatAccel",
        "title": tr("Lateral Acceleration"),
        "subtitle": tr("Maps steering torque to turning response."),
        "min_val": max(0.01, cs.latAccelFactor) * 0.5, "max_val": max(0.01, cs.latAccelFactor) * 1.5, "step": 0.01,
        "visible": lambda: alt_on() and cs.latAccelFactor != 0,
      },
      {
        "key": "SteerRatio",
        "title": tr("Steer Ratio"),
        "subtitle": tr("Relationship between steering wheel and road-wheel angle."),
        "min_val": max(0.01, cs.steerRatio) * 0.5, "max_val": max(0.01, cs.steerRatio) * 1.5, "step": 0.01,
        "visible": lambda: alt_on() and cs.steerRatio != 0,
      },
    ]

    tuning_toggles = [
      {
        "title": tr("Advanced Lateral Tuning"),
        "subtitle": tr("Fine-tune steering response and auto-tuning."),
        "get": lambda: p.get_bool("AdvancedLateralTune"),
        "set": lambda s: p.put_bool("AdvancedLateralTune", s),
      },
      {
        "title": tr("NNFF"),
        "subtitle": tr("Neural net feedforward steering controller."),
        "get": lambda: p.get_bool("NNFF"),
        "set": lambda s: (p.put_bool("NNFF", s),
                          s and p.put_bool("NNFFLite", False),
                          _sync_parent(p, "LateralTune", _LATERAL_TUNE_KEYS)),
        "is_enabled": lambda: cs.hasNNFFLog and not cs.isAngleCar,
        "disabled_label": tr("Not Available"),
        "visible": alt_on,
      },
      {
        "title": tr("NNFF Lite"),
        "subtitle": tr("Lightweight NNFF when full model is off."),
        "get": lambda: p.get_bool("NNFFLite"),
        "set": lambda s: (p.put_bool("NNFFLite", s),
                          _sync_parent(p, "LateralTune", _LATERAL_TUNE_KEYS)),
        "is_enabled": lambda: not cs.isAngleCar,
        "disabled_label": tr("Not Available"),
        "visible": alt_on,
      },
      {
        "title": tr("Force Torque Ctrl"),
        "subtitle": tr("Torque-based steering for smoother lane keeping."),
        "get": lambda: p.get_bool("ForceTorqueController"),
        "set": lambda s: (p.put_bool("ForceTorqueController", s),
                          _sync_parent(p, "LateralTune", _LATERAL_TUNE_KEYS)),
        "is_enabled": lambda: not cs.isTorqueCar and not cs.isAngleCar,
        "disabled_label": tr("Not Available"),
        "visible": alt_on,
      },
      {
        "title": tr("Force Turn Desires"),
        "subtitle": tr("Follow turn intent below min lane change speed."),
        "get": lambda: p.get_bool("TurnDesires"),
        "set": lambda s: (p.put_bool("TurnDesires", s),
                          _sync_parent(p, "LateralTune", _LATERAL_TUNE_KEYS)),
        "visible": alt_on,
      },
      {
        "title": tr("Force Auto-Tune On"),
        "subtitle": tr("Force-enable live auto-tuning for friction and lateral accel."),
        "get": lambda: p.get_bool("ForceAutoTune"),
        "set": lambda s: (p.put_bool("ForceAutoTune", s),
                          s and p.put_bool("ForceAutoTuneOff", False),
                          _sync_parent(p, "AdvancedLateralTune", _ADVANCED_LATERAL_KEYS)),
        "is_enabled": lambda: not cs.hasAutoTune and cs.isTorqueCar and not cs.isAngleCar,
        "disabled_label": tr("Not Available"),
        "visible": alt_on,
      },
      {
        "title": tr("Force Auto-Tune Off"),
        "subtitle": tr("Force-disable auto-tuning and use your set values."),
        "get": lambda: p.get_bool("ForceAutoTuneOff"),
        "set": lambda s: (p.put_bool("ForceAutoTuneOff", s),
                          s and p.put_bool("ForceAutoTune", False),
                          _sync_parent(p, "AdvancedLateralTune", _ADVANCED_LATERAL_KEYS)),
        "is_enabled": lambda: cs.hasAutoTune and cs.isTorqueCar and not cs.isAngleCar,
        "disabled_label": tr("Not Available"),
        "visible": alt_on,
      },
    ]

    self._sub_panels["tuning"] = SteeringSubPanelView(
      self,
      tr("Advanced Lateral Tuning"),
      tr("Fine-tune steering response, feedforward controllers, and auto-tuning."),
      tuning_adjustors, tuning_toggles,
    )

    self._wire_sub_panels()

  def _on_select(self, key: str):
    if key == "PauseAOLOnBrake":
      self._show_slider("PauseAOLOnBrake", 0, 100, unit=" mph")
    elif key == "PauseLateralSpeed":
      def on_speed_close(res, val):
        if res == DialogResult.CONFIRM:
          self._params.put_int("PauseLateralSpeed", int(val))
          self._params.put_bool("QOLLateral", int(val) > 0)
      current = self._params.get_int("PauseLateralSpeed")
      gui_app.push_widget(AetherSliderDialog(
        tr("Pause Lateral Below"), 0, 100, 1, current, on_speed_close,
        unit=" mph", color=self.SLIDER_COLOR))
    elif key == "LateralResumeDelay":
      self._show_slider("LateralResumeDelay", 0.0, 5.0, step=0.1, unit="s", value_type="float")
    elif key == "MinimumLaneChangeSpeed":
      self._show_slider("MinimumLaneChangeSpeed", 0, 100, unit=" mph")
    elif key == "LaneChangeTime":
      self._show_slider("LaneChangeTime", 0.0, 5.0, step=0.1, unit="s", value_type="float")
    elif key == "LaneDetectionWidth":
      self._show_slider("LaneDetectionWidth", 0.0, 15.0, step=0.1, unit=" ft", value_type="float")
    elif key == "LaneChangeSmoothing":
      self._show_lane_smoothing()
    elif key == "SteerDelay":
      self._show_slider("SteerDelay", 0.01, 1.0, step=0.01, unit="s", value_type="float")
    elif key == "SteerFriction":
      self._show_slider("SteerFriction", 0.0, max(1.0, starpilot_state.car_state.friction * 1.5), step=0.01, value_type="float")
    elif key == "SteerKP":
      self._show_slider("SteerKP", max(0.01, starpilot_state.car_state.steerKp) * 0.5, max(0.01, starpilot_state.car_state.steerKp) * 1.5, step=0.01, value_type="float")
    elif key == "SteerLatAccel":
      self._show_slider("SteerLatAccel", max(0.01, starpilot_state.car_state.latAccelFactor) * 0.5, max(0.01, starpilot_state.car_state.latAccelFactor) * 1.5, step=0.01, value_type="float")
    elif key == "SteerRatio":
      self._show_slider("SteerRatio", max(0.01, starpilot_state.car_state.steerRatio) * 0.5, max(0.01, starpilot_state.car_state.steerRatio) * 1.5, step=0.01, value_type="float")

  def _show_lane_smoothing(self):
    def on_close(res, val):
      if res == DialogResult.CONFIRM:
        self._params.put_int("LaneChangeSmoothing", int(val))
    current = self._params.get_int("LaneChangeSmoothing") if self._params.get_int("LaneChangeSmoothing") > 0 else 10
    gui_app.push_widget(AetherSliderDialog(tr("Lane Change Smoothing"), 1, 10, 1, current, on_close,
                                            color=self.SLIDER_COLOR))
