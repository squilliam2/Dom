from __future__ import annotations

from dataclasses import dataclass, replace
from collections.abc import Callable

import pyray as rl

from openpilot.selfdrive.ui.lib.starpilot_state import starpilot_state
from openpilot.system.ui.lib.application import FontWeight, MouseEvent, MousePos, gui_app
from openpilot.system.ui.lib.multilang import tr, tr_noop
from openpilot.system.ui.widgets import DialogResult, Widget
from openpilot.system.ui.widgets.confirm_dialog import ConfirmDialog
from openpilot.system.ui.widgets.keyboard import Keyboard
from openpilot.system.ui.widgets.option_dialog import MultiOptionDialog

from openpilot.selfdrive.ui.layouts.settings.starpilot.panel import _SettingsPage

from openpilot.selfdrive.ui.layouts.settings.starpilot.aethergrid import (
  AETHER_LIST_METRICS,
  AetherSliderDialog,
  DEFAULT_PANEL_STYLE,
  SettingRow,
  SettingSection,
  AetherSettingsView,
  AetherCategoryTileView,
  TileGrid,
  HubTile,
  hex_to_color,
)

from openpilot.starpilot.common.accel_profile import (
  ACCELERATION_PROFILES,
  DECELERATION_PROFILES,
  normalize_acceleration_profile,
  normalize_deceleration_profile,
)
from openpilot.starpilot.common.experimental_state import sync_persist_experimental_state


PANEL_STYLE = DEFAULT_PANEL_STYLE

ACCELERATION_PROFILE_OPTIONS = [
  (ACCELERATION_PROFILES["STANDARD"], "Standard"),
  (ACCELERATION_PROFILES["ECO"], "Eco"),
  (ACCELERATION_PROFILES["SPORT"], "Sport"),
  (ACCELERATION_PROFILES["SPORT_PLUS"], "Sport+"),
]

DECELERATION_PROFILE_OPTIONS = [
  (DECELERATION_PROFILES["STANDARD"], "Standard"),
  (DECELERATION_PROFILES["ECO"], "Eco"),
  (DECELERATION_PROFILES["SPORT"], "Sport"),
]


# ═══════════════════════════════════════════════════════════════
# AdaptiveSpeedView — nested panel with two adaptive speed tiles
# ═══════════════════════════════════════════════════════════════

class AdaptiveSpeedView(Widget):
  def __init__(self, controller):
    super().__init__()
    self._controller = controller
    self._grid = TileGrid(columns=2, padding=12)
    self._child(self._grid)

    self._grid.add_tile(HubTile(
      title=tr("Conditional Experimental"),
      desc=tr("Configure triggers and threshold speeds for automated Experimental Mode switching."),
      icon_key="steering",
      on_click=lambda: controller._navigate_to("ce"),
      bg_color="#8B5CF6",
    ))

    self._grid.add_tile(HubTile(
      title=tr("Curve Speed Controller"),
      desc=tr("Configure speed control on curves and reset collected calibration data."),
      icon_key="navigate",
      on_click=lambda: controller._navigate_to("csc"),
      bg_color="#8B5CF6",
    ))

  def _render(self, rect: rl.Rectangle):
    margin_x = 18.0
    margin_y = 24.0
    grid_x = rect.x + margin_x
    grid_y = rect.y + margin_y
    grid_w = rect.width - margin_x * 2
    grid_h = rect.y + rect.height - grid_y - margin_y
    self._grid.render(rl.Rectangle(grid_x, grid_y, grid_w, grid_h))


# ═══════════════════════════════════════════════════════════════
# LongitudinalManagerView — main category grid
# ═══════════════════════════════════════════════════════════════

class LongitudinalManagerView(AetherSettingsView):
  @property
  def vertical_scrolling_disabled(self) -> bool:
    return True

  def __init__(self, controller, sections, **kwargs):
    super().__init__(controller, sections, **kwargs)
    self._hero_grid = TileGrid(columns=3, padding=12)
    self._hero_grid.set_touch_valid_callback(lambda: self._scroll_panel.is_touch_valid())
    self._child(self._hero_grid)

    self._standard_grid = TileGrid(columns=3, padding=12)
    self._standard_grid.set_touch_valid_callback(lambda: self._scroll_panel.is_touch_valid())
    self._child(self._standard_grid)

    self._init_toggles()

  def _init_toggles(self):
    hero_data = [
      {
        "title": tr("Longitudinal Tuning"),
        "desc": tr("Configure acceleration profiles, smooth following, lane changes, and route speed control."),
        "icon": "steering",
        "color": "#8B5CF6",
        "on_click": lambda: gui_app.push_widget(
          AetherCategoryTileView(
            self._controller,
            tr("Longitudinal Tuning"),
            self._controller._tune_rows,
            color="#8B5CF6",
            subtitle=tr("Configure acceleration profiles, smooth following, lane changes, and route speed control."),
            panel_style=self._panel_style,
          )
        )
      },
      {
        "title": tr("Advanced Actuators"),
        "desc": tr("Adjust actuator delay, EV/Truck tuning, and launch/stop speeds/rates."),
        "icon": "vehicle",
        "color": "#8B5CF6",
        "on_click": lambda: gui_app.push_widget(
          AetherCategoryTileView(
            self._controller,
            tr("Advanced Actuators"),
            self._controller._advanced_rows,
            color="#8B5CF6",
            subtitle=tr("Adjust actuator delay, EV/Truck tuning, and launch/stop speeds/rates."),
            panel_style=self._panel_style,
          )
        )
      },
      {
        "title": tr("Speed Limit Controller"),
        "desc": tr("Manage auto speed matching, confirmation, offsets, and source priority."),
        "icon": "navigate",
        "color": "#8B5CF6",
        "on_click": lambda: gui_app.push_widget(
          AetherCategoryTileView(
            self._controller,
            tr("Speed Limit Controller"),
            self._controller._slc_rows,
            color="#8B5CF6",
            subtitle=tr("Manage auto speed matching, confirmation, offsets, and source priority."),
            panel_style=self._panel_style,
          )
        )
      },
    ]

    standard_data = [
      {
        "title": tr("Adaptive Speed Controls"),
        "desc": tr("Configure Curve Speed Controller and Conditional Experimental Mode triggers."),
        "icon": "display",
        "color": "#8B5CF6",
        "on_click": lambda: self._controller._navigate_to("adaptive_speed")
      },
      {
        "title": tr("Driving Personalities"),
        "desc": tr("Customize follow distance and jerk/response metrics for each personality profile."),
        "icon": "system",
        "color": "#8B5CF6",
        "on_click": lambda: gui_app.push_widget(
          AetherCategoryTileView(
            self._controller,
            tr("Driving Personalities"),
            self._controller._personality_rows,
            color="#8B5CF6",
            subtitle=tr("Customize follow distance and jerk/response metrics for each personality profile."),
            panel_style=self._panel_style,
          )
        )
      },
      {
        "title": tr("Daily QOL & Weather"),
        "desc": tr("Configure cruise intervals, standstill behaviors, gear mapping, and weather presets."),
        "icon": "sound",
        "color": "#8B5CF6",
        "on_click": lambda: gui_app.push_widget(
          AetherCategoryTileView(
            self._controller,
            tr("Daily QOL & Weather"),
            self._controller._daily_rows,
            color="#8B5CF6",
            subtitle=tr("Configure cruise intervals, standstill behaviors, gear mapping, and weather presets."),
            panel_style=self._panel_style,
          )
        )
      },
    ]

    self._hero_grid.clear()
    for d in hero_data:
      self._hero_grid.add_tile(
        HubTile(
          title=d["title"],
          desc=d["desc"],
          icon_key=d["icon"],
          on_click=d["on_click"],
          bg_color=d["color"],
        )
      )

    self._standard_grid.clear()
    for d in standard_data:
      self._standard_grid.add_tile(
        HubTile(
          title=d["title"],
          desc=d["desc"],
          icon_key=d["icon"],
          on_click=d["on_click"],
          bg_color=d["color"],
        )
      )

  def _render(self, rect: rl.Rectangle):
    self.set_rect(rect)
    self._interactive_rects.clear()

    margin_x = 18.0
    margin_y = 24.0

    grid_x = rect.x + margin_x
    grid_y = rect.y + margin_y
    grid_w = rect.width - margin_x * 2
    grid_h = rect.y + rect.height - grid_y - margin_y

    self._scroll_rect = rl.Rectangle(grid_x, grid_y, grid_w, grid_h)
    self._content_height = grid_h

    self._scroll_panel.set_enabled(self.is_visible)
    self._scroll_offset = self._scroll_panel.update(
      self._scroll_rect, self._scroll_rect.height
    )

    if self.vertical_scrolling_disabled:
      self._scroll_offset = 0.0

    self._draw_scroll_content(self._scroll_rect, self._scroll_rect.width)

  def _draw_scroll_content(self, rect: rl.Rectangle, width: float):
    y = rect.y + self._scroll_offset
    viewport_h = rect.height

    gap_y = 12.0
    padding_bottom = 6.0
    tile_space = viewport_h - gap_y - padding_bottom

    hero_h = tile_space * 0.55
    standard_h = tile_space * 0.45

    self._hero_grid._tile_height = hero_h
    self._standard_grid._tile_height = standard_h

    self._hero_grid.set_parent_rect(self._scroll_rect)
    self._hero_grid.render(rl.Rectangle(rect.x, y, width, hero_h))

    self._standard_grid.set_parent_rect(self._scroll_rect)
    self._standard_grid.render(rl.Rectangle(rect.x, y + hero_h + gap_y, width, standard_h))


# ═══════════════════════════════════════════════════════════════
# StarPilotLongitudinalLayout — controller
# ═══════════════════════════════════════════════════════════════

class StarPilotLongitudinalLayout(_SettingsPage):
  def __init__(self):
    super().__init__()
    self._keyboard = Keyboard(min_text_size=1)
    self._build_view()

  def _longitudinal_enabled(self) -> bool:
    return self._params.get_bool("LongitudinalTune")

  def _advanced_enabled(self) -> bool:
    return self._params.get_bool("AdvancedLongitudinalTune")

  def _using_human_acceleration(self) -> bool:
    return self._params.get_bool("LongitudinalTune") and self._params.get_bool("HumanAcceleration")

  def _show_stop_tuning_values(self) -> bool:
    return self._advanced_enabled() and not (starpilot_state.car_state.isToyota and self._params.get_bool("FrogsGoMoosTweak"))

  def _build_view(self):
    ol = lambda: starpilot_state.car_state.hasOpenpilotLongitudinal
    ce_on = lambda: self._params.get_bool("ConditionalExperimental")
    ce_lead = lambda: ce_on() and self._params.get_bool("CELead")
    csc_on = lambda: self._params.get_bool("CurveSpeedController")
    confirmation_on = lambda: self._params.get_bool("SLCConfirmation")

    # ── 1. Longitudinal Tuning Rows ──
    self._tune_rows = [
      SettingRow("LongitudinalTune", "toggle", tr_noop("Longitudinal Tuning"),
                 subtitle=tr_noop("Acceleration and braking control changes to fine-tune how openpilot drives."),
                 get_state=lambda: self._params.get_bool("LongitudinalTune"),
                 set_state=lambda s: self._params.put_bool("LongitudinalTune", s)),
      SettingRow("AccelProfile", "value", tr_noop("Acceleration Profile"),
                 subtitle=tr_noop("Choose how quickly openpilot speeds up."),
                 get_value=self._get_acceleration_profile_label,
                 on_click=self._show_acceleration_profile_selector,
                 visible=self._longitudinal_enabled),
      SettingRow("DecelProfile", "value", tr_noop("Deceleration Profile"),
                 subtitle=tr_noop("Choose how firmly openpilot slows the car down."),
                 get_value=self._get_deceleration_profile_label,
                 on_click=self._show_deceleration_profile_selector,
                 visible=self._longitudinal_enabled),
      SettingRow("PrioritizeSmoothFollowing", "toggle", tr_noop("Prioritize Smooth Following"),
                 subtitle=tr_noop("Disables the newer far-lead follow logic on cars that show lead-follow stutter. Tradeoff: it may react later in some edge-case lead approaches."),
                 get_state=lambda: self._params.get_bool("PrioritizeSmoothFollowing"),
                 set_state=lambda s: self._params.put_bool("PrioritizeSmoothFollowing", s),
                 visible=self._longitudinal_enabled),
      SettingRow("HumanLaneChanges", "toggle", tr_noop("Human-Like Lane Changes"),
                 subtitle=tr_noop("Radar-informed behavior during lane changes."),
                 get_state=lambda: self._params.get_bool("HumanLaneChanges"),
                 set_state=lambda s: self._params.put_bool("HumanLaneChanges", s),
                 visible=lambda: self._longitudinal_enabled() and starpilot_state.car_state.hasRadar),
      SettingRow("LeadDetection", "value", tr_noop("Lead Detection Sensitivity"),
                 subtitle=tr_noop("Control how aggressively openpilot detects and reacts to vehicles ahead."),
                 get_value=lambda: f"{self._params.get_int('LeadDetectionThreshold')}%",
                 on_click=lambda: self._show_slider("LeadDetectionThreshold", 25, 50, unit="%"),
                 visible=self._longitudinal_enabled),
      SettingRow("NavLongitudinalAllowed", "toggle", tr_noop("Use Route Speed Control"),
                 subtitle=tr_noop("Allow an active navigation route to reduce cruise speed for upcoming turns, ramps, and roundabouts."),
                 get_state=lambda: self._params.get_bool("NavLongitudinalAllowed"),
                 set_state=lambda s: self._params.put_bool("NavLongitudinalAllowed", s),
                 visible=self._longitudinal_enabled),
    ]

    # ── 2. Advanced Actuators Rows ──
    adv = self._advanced_enabled
    self._advanced_rows = [
      SettingRow("AdvancedLongitudinalTune", "toggle", tr_noop("Advanced Longitudinal Tuning"),
                 subtitle=tr_noop("Advanced acceleration and braking changes for refining launch, stopping, and actuator response."),
                 get_state=lambda: self._params.get_bool("AdvancedLongitudinalTune"),
                 set_state=lambda s: self._params.put_bool("AdvancedLongitudinalTune", s)),
      SettingRow("EVTuning", "toggle", tr_noop("EV Tuning"),
                 subtitle=tr_noop("Acceleration tuning for EV and direct-drive vehicles."),
                 get_state=lambda: self._params.get_bool("EVTuning"),
                 set_state=self._set_ev_tuning,
                 visible=adv,
                 enabled=lambda: not self._params.get_bool("TruckTuning"),
                 disabled_label=tr_noop("Truck Active")),
      SettingRow("TruckTuning", "toggle", tr_noop("Truck Tuning"),
                 subtitle=tr_noop("Stronger launch and acceleration for heavier vehicles."),
                 get_state=lambda: self._params.get_bool("TruckTuning"),
                 set_state=self._set_truck_tuning,
                 visible=adv,
                 enabled=lambda: not self._params.get_bool("EVTuning"),
                 disabled_label=tr_noop("EV Active")),
      SettingRow("TrailerLoad", "value", tr_noop("Trailer Load"),
                 subtitle=tr_noop("Loaded trailer weight for tow-aware gas, brake, and conservative lateral assist."),
                 get_value=lambda: f"{self._params.get_int('TrailerLoad')} lb",
                 on_click=lambda: self._show_slider("TrailerLoad", 0, 15000, step=500, unit=" lb"),
                 visible=adv),
      SettingRow("ActuatorDelay", "value", tr_noop("Actuator Delay"),
                 subtitle=tr_noop("Time between command and the vehicle's response."),
                 get_value=lambda: f"{self._params.get_float('LongitudinalActuatorDelay'):.2f}s",
                 on_click=lambda: self._show_slider("LongitudinalActuatorDelay", 0.0, 1.0, step=0.01, unit="s", value_type="float"),
                 visible=adv),
      SettingRow("MaxAccel", "value", tr_noop("Maximum Acceleration"),
                 subtitle=tr_noop("Strongest acceleration openpilot is allowed to command."),
                 get_value=lambda: f"{self._params.get_float('MaxDesiredAcceleration'):.1f}m/s" if self._params.get_float("MaxDesiredAcceleration") is not None else "N/A",
                 on_click=lambda: self._show_slider("MaxDesiredAcceleration", 0.1, 4.0, step=0.1, unit="m/s", value_type="float"),
                 visible=adv),
      SettingRow("StartAccel", "value", tr_noop("Start Acceleration"),
                 subtitle=tr_noop("Extra acceleration when moving away from a stop."),
                 get_value=lambda: f"{self._params.get_float('StartAccel'):.2f}m/s",
                 on_click=lambda: self._show_slider("StartAccel", 0.0, 4.0, step=0.01, unit="m/s", value_type="float"),
                 visible=lambda: adv() and not self._using_human_acceleration()),
      SettingRow("StopAccel", "value", tr_noop("Stop Acceleration"),
                 subtitle=tr_noop("Brake force to hold the vehicle at a complete stop."),
                 get_value=lambda: f"{self._params.get_float('StopAccel'):.2f}m/s",
                 on_click=lambda: self._show_slider("StopAccel", -4.0, 0.0, step=0.01, unit="m/s", value_type="float"),
                 visible=adv),
      SettingRow("StoppingRate", "value", tr_noop("Stopping Rate"),
                 subtitle=tr_noop("How quickly braking ramps up to bring the car to a stop."),
                 get_value=lambda: f"{self._params.get_float('StoppingDecelRate'):.3f}m/s",
                 on_click=lambda: self._show_slider("StoppingDecelRate", 0.001, 1.0, step=0.001, unit="m/s", value_type="float"),
                 visible=self._show_stop_tuning_values),
      SettingRow("StartSpeed", "value", tr_noop("Start Speed"),
                 subtitle=tr_noop("Speed where openpilot exits the stopped state."),
                 get_value=lambda: f"{self._params.get_float('VEgoStarting'):.2f}m/s",
                 on_click=lambda: self._show_slider("VEgoStarting", 0.01, 1.0, step=0.01, unit="m/s", value_type="float"),
                 visible=self._show_stop_tuning_values),
      SettingRow("StopSpeed", "value", tr_noop("Stop Speed"),
                 subtitle=tr_noop("Speed where openpilot considers the vehicle fully stopped."),
                 get_value=lambda: f"{self._params.get_float('VEgoStopping'):.2f}m/s",
                 on_click=lambda: self._show_slider("VEgoStopping", 0.01, 1.0, step=0.01, unit="m/s", value_type="float"),
                 visible=self._show_stop_tuning_values),
    ]

    # ── 3. Speed Limit Controller (SLC) Rows ──
    self._slc_rows = [
      SettingRow("SLC", "toggle", tr_noop("Speed Limit Controller"),
                 subtitle=tr_noop("Limit the car's maximum speed to the current speed limit."),
                 get_state=lambda: self._params.get_bool("SpeedLimitController"),
                 set_state=lambda s: self._params.put_bool("SpeedLimitController", s)),
      SettingRow("SLCFallback", "value", tr_noop("Fallback Speed"),
                 subtitle="",
                 get_value=lambda: self._params.get("SLCFallback", encoding="utf-8") or "Set Speed",
                 on_click=lambda: self._show_string_select("SLCFallback", ["Set Speed", "Experimental Mode", "Previous Limit"])),
      SettingRow("SLCOverride", "value", tr_noop("Override Speed"),
                 subtitle="",
                 get_value=lambda: self._params.get("SLCOverride", encoding="utf-8") or "None",
                 on_click=lambda: self._show_string_select("SLCOverride", ["None", "Set With Gas Pedal", "Max Set Speed"])),
      SettingRow("SLCPriority", "value", tr_noop("Source Priority"),
                 subtitle="",
                 get_value=self._get_priority_value,
                 on_click=self._on_priority_clicked),
      SettingRow("SetSpeedLimit", "toggle", tr_noop("Auto Match Speed Limits"),
                 subtitle="",
                 get_state=lambda: self._params.get_bool("SetSpeedLimit"),
                 set_state=lambda s: self._params.put_bool("SetSpeedLimit", s)),
      SettingRow("SLCConfirmation", "toggle", tr_noop("Confirm New Limits"),
                 subtitle="",
                 get_state=lambda: self._params.get_bool("SLCConfirmation"),
                 set_state=lambda s: self._params.put_bool("SLCConfirmation", s)),
      SettingRow("SLCConfirmationLower", "toggle", tr_noop("Confirm Lower"),
                 subtitle="",
                 get_state=lambda: self._params.get_bool("SLCConfirmationLower"),
                 set_state=lambda s: self._params.put_bool("SLCConfirmationLower", s),
                 visible=confirmation_on),
      SettingRow("SLCConfirmationHigher", "toggle", tr_noop("Confirm Higher"),
                 subtitle="",
                 get_state=lambda: self._params.get_bool("SLCConfirmationHigher"),
                 set_state=lambda s: self._params.put_bool("SLCConfirmationHigher", s),
                 visible=confirmation_on),
      SettingRow("SLCLookHigher", "value", tr_noop("Higher Lookahead"),
                 subtitle="",
                 get_value=lambda: f"{self._params.get_int('SLCLookaheadHigher')}s",
                 on_click=lambda: self._show_slider("SLCLookaheadHigher", 0, 30, unit="s")),
      SettingRow("SLCLookLower", "value", tr_noop("Lower Lookahead"),
                 subtitle="",
                 get_value=lambda: f"{self._params.get_int('SLCLookaheadLower')}s",
                 on_click=lambda: self._show_slider("SLCLookaheadLower", 0, 30, unit="s")),
      SettingRow("SLCMapbox", "toggle", tr_noop("Mapbox Fallback"),
                 subtitle="",
                 get_state=lambda: self._params.get_bool("SLCMapboxFiller"),
                 set_state=lambda s: self._params.put_bool("SLCMapboxFiller", s)),
      SettingRow("VisionSpeedLimit", "toggle", tr_noop("Vision Detection"),
                 subtitle=tr_noop("Use the road camera to detect speed limit signs for SLC."),
                 get_state=lambda: self._params.get_bool("VisionSpeedLimitDetection"),
                 set_state=lambda s: self._params.put_bool("VisionSpeedLimitDetection", s)),
      SettingRow("ShowSLCOffset", "toggle", tr_noop("Show SLC Offset"),
                 subtitle="",
                 get_state=lambda: self._params.get_bool("ShowSLCOffset"),
                 set_state=lambda s: self._params.put_bool("ShowSLCOffset", s)),
      SettingRow("ShowSources", "toggle", tr_noop("Show Sources"),
                 subtitle="",
                 get_state=lambda: self._params.get_bool("SpeedLimitSources"),
                 set_state=lambda s: self._params.put_bool("SpeedLimitSources", s)),
      SettingRow("ConfigureOffsets", "value", tr_noop("SLC Offsets"),
                 subtitle=tr_noop("Per-limit speed adjustments for the Speed Limit Controller."),
                 get_value=lambda: tr_noop("Configure"),
                 on_click=self._show_slc_offsets_category),
    ]

    # Initialize SLC Offsets rows
    self._slc_offset_rows = []
    for i in range(1, 8):
      key = f"Offset{i}"
      self._slc_offset_rows.append(SettingRow(
        f"Offset{i}", "value", tr_noop(f"Offset {i}"),
        subtitle="",
        get_value=lambda k=key: f"{self._params.get_int(k)}{self._speed_unit()}",
        on_click=lambda k=key: self._show_slider(k, *self._speed_range(), unit=self._speed_unit()),
      ))

    # ── 4. Adaptive Speed Controls Rows (CES + CSC) ──
    self._conditional_experimental_rows = [
      SettingRow("ConditionalExperimental", "toggle", tr_noop("Conditional Experimental Mode"),
                 subtitle="",
                 get_state=lambda: self._params.get_bool("ConditionalExperimental"),
                 set_state=lambda s: self._params.put_bool("ConditionalExperimental", s)),
      SettingRow("PersistExp", "toggle", tr_noop("Persist Experimental State"),
                 subtitle=tr_noop("Keep override through reboots until manually cleared."),
                 get_state=lambda: self._params.get_bool("PersistExperimentalState"),
                 set_state=self._set_persist_experimental_state,
                 visible=ce_on),
      SettingRow("CESpeed", "value", tr_noop("Below Speed"),
                 subtitle="",
                 get_value=lambda: f"{self._params.get_int('CESpeed')} mph",
                 on_click=lambda: self._show_slider("CESpeed", 0, 100, unit=" mph"),
                 visible=ce_on),
      SettingRow("CECurves", "toggle", tr_noop("Curves"),
                 subtitle="",
                 get_state=lambda: self._params.get_bool("CECurves"),
                 set_state=lambda s: self._params.put_bool("CECurves", s),
                 visible=ce_on),
      SettingRow("CECurvesLead", "toggle", tr_noop("Curves Lead"),
                 subtitle="",
                 get_state=lambda: self._params.get_bool("CECurvesLead"),
                 set_state=lambda s: self._params.put_bool("CECurvesLead", s),
                 visible=lambda: ce_on() and self._params.get_bool("CECurves")),
      SettingRow("CEStopLights", "toggle", tr_noop("Stop Lights"),
                 subtitle="",
                 get_state=lambda: self._params.get_bool("CEStopLights"),
                 set_state=lambda s: self._params.put_bool("CEStopLights", s),
                 visible=ce_on),
      SettingRow("CELead", "toggle", tr_noop("Lead Detected"),
                 subtitle="",
                 get_state=lambda: self._params.get_bool("CELead"),
                 set_state=lambda s: self._params.put_bool("CELead", s),
                 visible=ce_on),
      SettingRow("CESlowerLead", "toggle", tr_noop("Slower Lead"),
                 subtitle="",
                 get_state=lambda: self._params.get_bool("CESlowerLead"),
                 set_state=lambda s: self._params.put_bool("CESlowerLead", s),
                 visible=ce_lead),
      SettingRow("CEStoppedLead", "toggle", tr_noop("Stopped Lead"),
                 subtitle="",
                 get_state=lambda: self._params.get_bool("CEStoppedLead"),
                 set_state=lambda s: self._params.put_bool("CEStoppedLead", s),
                 visible=ce_lead),
      SettingRow("CEModelStopTime", "value", tr_noop("Predicted Stop"),
                 subtitle="",
                 get_value=lambda: f"{self._params.get_int('CEModelStopTime')}s",
                 on_click=lambda: self._show_slider("CEModelStopTime", 0, 10, unit="s"),
                 visible=ce_on),
      SettingRow("CESignalSpeed", "value", tr_noop("Signal Below"),
                 subtitle="",
                 get_value=lambda: f"{self._params.get_int('CESignalSpeed')} mph",
                 on_click=lambda: self._show_slider("CESignalSpeed", 0, 100, unit=" mph"),
                 visible=ce_on),
      SettingRow("CESpeedLead", "value", tr_noop("Speed Lead"),
                 subtitle="",
                 get_value=lambda: f"{self._params.get_int('CESpeedLead')} mph",
                 on_click=lambda: self._show_slider("CESpeedLead", 0, 100, unit=" mph"),
                 visible=ce_on),
      SettingRow("CESignalLaneDetection", "toggle", tr_noop("Signal Lane Detection"),
                 subtitle="",
                 get_state=lambda: self._params.get_bool("CESignalLaneDetection"),
                 set_state=lambda s: self._params.put_bool("CESignalLaneDetection", s),
                 visible=lambda: ce_on() and self._params.get_int("CESignalSpeed") > 0),
      SettingRow("ShowCEMStatus", "toggle", tr_noop("Status Widget"),
                 subtitle="",
                 get_state=lambda: self._params.get_bool("ShowCEMStatus"),
                 set_state=lambda s: self._params.put_bool("ShowCEMStatus", s),
                 visible=ce_on),
    ]

    self._curve_speed_controller_rows = [
      SettingRow("CurveSpeed", "toggle", tr_noop("Curve Speed Controller"),
                 subtitle="",
                 get_state=lambda: self._params.get_bool("CurveSpeedController"),
                 set_state=lambda s: self._params.put_bool("CurveSpeedController", s)),
      SettingRow("ShowCSCStatus", "toggle", tr_noop("Status Widget"),
                 subtitle=tr_noop("Show the Curve Speed Controller ambient effect on the driving screen."),
                 get_state=lambda: self._params.get_bool("ShowCSCStatus"),
                 set_state=lambda s: self._params.put_bool("ShowCSCStatus", s),
                 visible=csc_on),
      SettingRow("CalibratedLatAccel", "value", tr_noop("Calibrated Lateral Accel"),
                 subtitle=tr_noop("The learned lateral acceleration from collected driving data. Higher values allow faster cornering."),
                 get_value=lambda: f"{self._params_memory.get_float('CalibratedLateralAcceleration'):.2f} m/s",
                 on_click=None,
                 visible=csc_on),
      SettingRow("CalibrationProgress", "value", tr_noop("Calibration Progress"),
                 subtitle=tr_noop("How much curve data has been collected. Normal for the value to stay low."),
                 get_value=lambda: f"{self._params_memory.get_float('CalibrationProgress'):.2f}%",
                 on_click=None,
                 visible=csc_on),
      SettingRow("ResetCurve", "action", tr_noop("Reset Curve Data"),
                 subtitle=tr_noop("Reset collected user data for Curve Speed Controller."),
                 action_text=tr_noop("Reset"),
                 action_danger=True,
                 on_click=self._reset_curve_data,
                 visible=csc_on),
    ]

    # ── 5. Driving Personalities Rows ──
    self._personality_rows = [
      SettingRow("PersonalitiesToggle", "toggle", tr_noop("Driving Personalities"),
                 subtitle="",
                 get_state=lambda: self._params.get_bool("CustomPersonalities"),
                 set_state=lambda s: self._params.put_bool("CustomPersonalities", s)),
      SettingRow("Traffic", "value", tr_noop("Traffic"),
                 subtitle=tr_noop("Configure follow distance, smoothness, and response for traffic conditions."),
                 get_value=lambda: tr_noop("Configure"),
                 on_click=lambda: self._show_personality_profile_category("Traffic")),
      SettingRow("Aggressive", "value", tr_noop("Aggressive"),
                 subtitle=tr_noop("Configure follow distance, smoothness, and response for aggressive driving."),
                 get_value=lambda: tr_noop("Configure"),
                 on_click=lambda: self._show_personality_profile_category("Aggressive")),
      SettingRow("Standard", "value", tr_noop("Standard"),
                 subtitle=tr_noop("Configure follow distance, smoothness, and response for everyday driving."),
                 get_value=lambda: tr_noop("Configure"),
                 on_click=lambda: self._show_personality_profile_category("Standard")),
      SettingRow("Relaxed", "value", tr_noop("Relaxed"),
                 subtitle=tr_noop("Configure follow distance, smoothness, and response for relaxed driving."),
                 get_value=lambda: tr_noop("Configure"),
                 on_click=lambda: self._show_personality_profile_category("Relaxed")),
    ]

    # ── 6. Daily QOL & Weather Rows ──
    self._daily_rows = [
      SettingRow("QOLToggle", "toggle", tr_noop("Quality of Life"),
                 subtitle="",
                 get_state=lambda: self._params.get_bool("QOLLongitudinal"),
                 set_state=lambda s: self._params.put_bool("QOLLongitudinal", s)),
      SettingRow("CustomCruise", "value", tr_noop("Cruise Interval"),
                 subtitle="",
                 get_value=lambda: f"{max(1, self._params.get_int('CustomCruise'))} mph",
                 on_click=lambda: self._show_slider("CustomCruise", 1, 100, unit=" mph",
                                                    current_value=max(1, self._params.get_int("CustomCruise"))),
                 visible=lambda: self._params.get_bool("QOLLongitudinal")),
      SettingRow("CustomCruiseLong", "value", tr_noop("Cruise Long"),
                 subtitle="",
                 get_value=lambda: f"{max(1, self._params.get_int('CustomCruiseLong'))} mph",
                 on_click=lambda: self._show_slider("CustomCruiseLong", 1, 100, unit=" mph",
                                                    current_value=max(1, self._params.get_int("CustomCruiseLong"))),
                 visible=lambda: self._params.get_bool("QOLLongitudinal")),
      SettingRow("ForceStops", "toggle", tr_noop("Force Stops"),
                 subtitle="",
                 get_state=lambda: self._params.get_bool("ForceStops"),
                 set_state=lambda s: self._params.put_bool("ForceStops", s),
                 visible=lambda: self._params.get_bool("QOLLongitudinal")),
      SettingRow("ForceStopDist", "value", tr_noop("Force Stop Offset"),
                 subtitle="",
                 get_value=lambda: f"{self._params.get_int('ForceStopDistanceOffset'):+d} ft",
                 on_click=lambda: self._show_slider("ForceStopDistanceOffset", -20, 20, unit=" ft"),
                 visible=lambda: self._params.get_bool("QOLLongitudinal") and self._params.get_bool("ForceStops")),
      SettingRow("RadarTakeoffs", "toggle", tr_noop("Radar for Takeoffs"),
                 subtitle=tr_noop("Turns on/off using radar data to track leads at standstill, making following/takeoffs more responsive once leads move."),
                 get_state=lambda: self._params.get_bool("RadarTakeoffs"),
                 set_state=lambda s: self._params.put_bool("RadarTakeoffs", s),
                 visible=lambda: self._params.get_bool("QOLLongitudinal") and starpilot_state.car_state.hasRadar),
      SettingRow("ForceStandstill", "toggle", tr_noop("Force Standstill"),
                 subtitle="",
                 get_state=lambda: self._params.get_bool("ForceStandstill"),
                 set_state=lambda s: self._params.put_bool("ForceStandstill", s),
                 visible=lambda: self._params.get_bool("QOLLongitudinal")),
      SettingRow("IncStoppedDist", "value", tr_noop("Stopped Distance"),
                 subtitle="",
                 get_value=lambda: f"{self._params.get_int('IncreasedStoppedDistance')} ft",
                 on_click=lambda: self._show_slider("IncreasedStoppedDistance", 0, 10, unit=" ft"),
                 visible=lambda: self._params.get_bool("QOLLongitudinal")),
      SettingRow("SetSpeedOffset", "value", tr_noop("Set Speed Offset"),
                 subtitle="",
                 get_value=lambda: f"+{self._params.get_int('SetSpeedOffset')} mph",
                 on_click=lambda: self._show_slider("SetSpeedOffset", 0, 99, unit=" mph"),
                 visible=lambda: self._params.get_bool("QOLLongitudinal")),
      SettingRow("MapGears", "toggle", tr_noop("Map Gears"),
                 subtitle="",
                 get_state=lambda: self._params.get_bool("MapGears"),
                 set_state=lambda s: self._params.put_bool("MapGears", s),
                 visible=lambda: self._params.get_bool("QOLLongitudinal")),
      SettingRow("MapAccel", "toggle", tr_noop("Map Acceleration"),
                 subtitle="",
                 get_state=lambda: self._params.get_bool("MapAcceleration"),
                 set_state=lambda s: self._params.put_bool("MapAcceleration", s),
                 visible=lambda: self._params.get_bool("QOLLongitudinal") and self._params.get_bool("MapGears")),
      SettingRow("MapDecel", "toggle", tr_noop("Map Deceleration"),
                 subtitle="",
                 get_state=lambda: self._params.get_bool("MapDeceleration"),
                 set_state=lambda s: self._params.put_bool("MapDeceleration", s),
                 visible=lambda: self._params.get_bool("QOLLongitudinal") and self._params.get_bool("MapGears")),
      SettingRow("WeatherPresets", "toggle", tr_noop("Weather Condition Offsets"),
                 subtitle=tr_noop("Automatically adjust driving behavior based on real-time weather."),
                 get_state=lambda: self._params.get_bool("WeatherPresets"),
                 set_state=lambda s: self._params.put_bool("WeatherPresets", s),
                 visible=lambda: self._params.get_bool("QOLLongitudinal")),
      SettingRow("LowVisibility", "value", tr_noop("Low Visibility"),
                 subtitle=tr_noop("Adjust parameters for fog, mist, and poor visibility conditions."),
                 get_value=lambda: tr_noop("Configure"),
                 on_click=lambda: self._show_weather_offsets_category("LowVisibility", tr_noop("Low Visibility")),
                 visible=lambda: self._params.get_bool("QOLLongitudinal") and self._params.get_bool("WeatherPresets")),
      SettingRow("Rain", "value", tr_noop("Rain"),
                 subtitle=tr_noop("Adjust parameters for light to moderate rain."),
                 get_value=lambda: tr_noop("Configure"),
                 on_click=lambda: self._show_weather_offsets_category("Rain", tr_noop("Rain")),
                 visible=lambda: self._params.get_bool("QOLLongitudinal") and self._params.get_bool("WeatherPresets")),
      SettingRow("RainStorm", "value", tr_noop("Rainstorms"),
                 subtitle=tr_noop("Adjust parameters for heavy rain and storms."),
                 get_value=lambda: tr_noop("Configure"),
                 on_click=lambda: self._show_weather_offsets_category("RainStorm", tr_noop("Rainstorms")),
                 visible=lambda: self._params.get_bool("QOLLongitudinal") and self._params.get_bool("WeatherPresets")),
      SettingRow("Snow", "value", tr_noop("Snow"),
                 subtitle=tr_noop("Adjust parameters for snowy and icy conditions."),
                 get_value=lambda: tr_noop("Configure"),
                 on_click=lambda: self._show_weather_offsets_category("Snow", tr_noop("Snow")),
                 visible=lambda: self._params.get_bool("QOLLongitudinal") and self._params.get_bool("WeatherPresets")),
      SettingRow("WeatherKey", "action", tr_noop("Set Weather Key"),
                 subtitle=tr_noop("Enter or remove your weather data API key."),
                 action_text=tr_noop("Set Key"),
                 on_click=self._set_weather_key,
                 visible=lambda: self._params.get_bool("QOLLongitudinal")),
    ]

    self._manager_view = LongitudinalManagerView(
      self, [],
      header_title=tr_noop("Gas/Brake"),
      header_subtitle=tr_noop("Fine-tune acceleration, braking, and driving behavior."),
      panel_style=PANEL_STYLE,
    )

    ce_rows = self._conditional_experimental_rows
    self._sub_panels["ce"] = AetherSettingsView(
      self,
      [
        SettingSection(tr("Conditional Experimental"), [x for x in ce_rows if x.type != "toggle"], column_pair="1"),
        SettingSection(tr("Conditional Experimental"), [x for x in ce_rows if x.type == "toggle"], column_pair="1"),
      ],
      header_title=tr("Conditional Experimental"),
      header_subtitle=tr("Configure triggers and threshold speeds for automated Experimental Mode switching."),
      panel_style=PANEL_STYLE,
    )

    csc_rows = self._curve_speed_controller_rows
    self._sub_panels["csc"] = AetherSettingsView(
      self,
      [
        SettingSection(tr("Curve Speed Controller"), [x for x in csc_rows if x.type != "toggle"], column_pair="1"),
        SettingSection(tr("Curve Speed Controller"), [x for x in csc_rows if x.type == "toggle"], column_pair="1"),
      ],
      header_title=tr("Curve Speed Controller"),
      header_subtitle=tr("Configure speed control on curves and reset collected calibration data."),
      panel_style=PANEL_STYLE,
    )

    self._sub_panels["adaptive_speed"] = AdaptiveSpeedView(self)
    self._wire_sub_panels()

  def _get_priority_value(self) -> str:
    primary = self._params.get("SLCPriority1", encoding="utf-8") or "Map Data"
    secondary = self._params.get("SLCPriority2", encoding="utf-8") or "None"
    if primary in ("Highest", "Lowest") or secondary in ("", "None", primary):
      return primary
    return f"{primary}, {secondary}"

  def _on_priority_clicked(self):
    primary_options = ["Dashboard", "Map Data", "Vision", "Highest", "Lowest"]
    current_primary = self._params.get("SLCPriority1", encoding="utf-8") or "Map Data"
    current_secondary = self._params.get("SLCPriority2", encoding="utf-8") or "None"

    def on_secondary_select(primary, dialog, res):
      if res == DialogResult.CONFIRM and dialog.selection:
        self._params.put("SLCPriority1", primary)
        self._params.put("SLCPriority2", dialog.selection)

    def show_secondary_dialog(primary):
      secondary_options = ["None"] + [option for option in ("Dashboard", "Map Data", "Vision") if option != primary]
      selected_secondary = current_secondary if current_secondary in secondary_options else "None"
      secondary_dialog = MultiOptionDialog(tr("SLC Secondary Priority"), secondary_options, selected_secondary,
                                           callback=lambda res: on_secondary_select(primary, secondary_dialog, res))
      gui_app.push_widget(secondary_dialog)

    def on_primary_select(res):
      if res != DialogResult.CONFIRM or not primary_dialog.selection:
        return
      if primary_dialog.selection in ("Highest", "Lowest"):
        self._params.put("SLCPriority1", primary_dialog.selection)
        self._params.put("SLCPriority2", "None")
        return
      show_secondary_dialog(primary_dialog.selection)

    primary_dialog = MultiOptionDialog(tr("SLC Primary Priority"), primary_options, current_primary, callback=on_primary_select)
    gui_app.push_widget(primary_dialog)

  def _get_acceleration_profile_label(self) -> str:
    value = normalize_acceleration_profile(self._params.get("AccelerationProfile", encoding="utf-8"))
    return self._profile_label_for_value(value, ACCELERATION_PROFILE_OPTIONS)

  def _get_deceleration_profile_label(self) -> str:
    value = normalize_deceleration_profile(self._params.get("DecelerationProfile", encoding="utf-8"))
    return self._profile_label_for_value(value, DECELERATION_PROFILE_OPTIONS)

  def _show_acceleration_profile_selector(self):
    self._show_labeled_select("Acceleration Profile", "AccelerationProfile", ACCELERATION_PROFILE_OPTIONS,
                              normalize_acceleration_profile(self._params.get("AccelerationProfile", encoding="utf-8")))

  def _show_deceleration_profile_selector(self):
    self._show_labeled_select("Deceleration Profile", "DecelerationProfile", DECELERATION_PROFILE_OPTIONS,
                              normalize_deceleration_profile(self._params.get("DecelerationProfile", encoding="utf-8")))

  def _profile_label_for_value(self, value, options) -> str:
    for option_value, option_label in options:
      if option_value == value:
        return tr(option_label)
    return tr(options[0][1])

  def _set_ev_tuning(self, state: bool):
    self._params.put_bool("EVTuning", state)
    if state:
      self._params.put_bool("TruckTuning", False)

  def _set_truck_tuning(self, state: bool):
    self._params.put_bool("TruckTuning", state)
    if state:
      self._params.put_bool("EVTuning", False)

  def _set_persist_experimental_state(self, state: bool):
    sync_persist_experimental_state(self._params, self._params_memory, state)

  def _reset_curve_data(self):
    def on_close(res):
      if res == DialogResult.CONFIRM:
        self._params.put_float("CalibratedLateralAcceleration", 2.00)
        self._params.remove("CalibrationProgress")
        self._params.remove("CurvatureData")

    gui_app.push_widget(ConfirmDialog(tr_noop("Reset Curve Data?"), tr_noop("Confirm"), callback=on_close))

  def _reset_profile(self, profile: str):
    def on_close(res):
      if res == DialogResult.CONFIRM:
        for key in ["Follow", "FollowHigh", "JerkAcceleration", "JerkDeceleration", "JerkDanger", "JerkSpeedDecrease", "JerkSpeed"]:
          self._params.remove(profile + key)

    gui_app.push_widget(ConfirmDialog(tr_noop("Reset to Defaults?"), tr_noop("Confirm"), callback=on_close))

  def _is_metric(self) -> bool:
    return self._params.get_bool("IsMetric")

  def _speed_unit(self) -> str:
    return " km/h" if self._is_metric() else " mph"

  def _speed_range(self) -> tuple[int, int]:
    return (-150, 150) if self._is_metric() else (-99, 99)

  def _show_slc_offsets_category(self):
    gui_app.push_widget(
      AetherCategoryTileView(
        self,
        tr("SLC Offsets"),
        self._slc_offset_rows,
        color="#8B5CF6",
        subtitle=tr("Per-limit speed adjustments for the Speed Limit Controller."),
        panel_style=PANEL_STYLE,
      )
    )

  def _show_personality_profile_category(self, profile: str):
    rows = self._build_personality_profile_rows(profile)
    gui_app.push_widget(
      AetherCategoryTileView(
        self,
        tr(f"{profile} Profile"),
        rows,
        color="#8B5CF6",
        subtitle=tr("Customize follow distance and smoothness for this driving personality."),
        panel_style=PANEL_STYLE,
      )
    )

  def _show_weather_offsets_category(self, suffix: str, title: str):
    rows = self._build_weather_offsets_rows(suffix)
    gui_app.push_widget(
      AetherCategoryTileView(
        self,
        tr(title),
        rows,
        color="#8B5CF6",
        subtitle=tr("Adjust driving parameters for this weather condition."),
        panel_style=PANEL_STYLE,
      )
    )

  def _build_personality_profile_rows(self, profile: str) -> list[SettingRow]:
    follow_min = 1.0 if profile == "Traffic" else 0.5
    follow_max = 2.5 if profile == "Traffic" else 3.0
    p = profile
    rows = [
      SettingRow(f"{p}Follow", "value", tr_noop("Follow Distance"),
                 subtitle="",
                 get_value=lambda: f"{self._params.get_float(p + 'Follow'):.2f}s",
                 on_click=lambda: self._show_slider(p + "Follow", follow_min, follow_max, step=0.05, unit="s", value_type="float")),
    ]
    if profile != "Traffic":
      rows.append(
        SettingRow(f"{p}FollowHigh", "value", tr_noop("Follow High"),
                   subtitle="",
                   get_value=lambda: f"{self._params.get_float(p + 'FollowHigh'):.2f}s",
                   on_click=lambda: self._show_slider(p + "FollowHigh", 1.0, 3.0, step=0.05, unit="s", value_type="float"))
      )
    rows.extend([
      SettingRow(f"{p}JerkAccel", "value", tr_noop("Accel Smoothness"),
                 subtitle="",
                 get_value=lambda: f"{self._params.get_int(p + 'JerkAcceleration')}%",
                 on_click=lambda: self._show_slider(p + "JerkAcceleration", 25, 200, step=5, unit="%")),
      SettingRow(f"{p}JerkDecel", "value", tr_noop("Brake Smoothness"),
                 subtitle="",
                 get_value=lambda: f"{self._params.get_int(p + 'JerkDeceleration')}%",
                 on_click=lambda: self._show_slider(p + "JerkDeceleration", 25, 200, step=5, unit="%")),
      SettingRow(f"{p}JerkDanger", "value", tr_noop("Safety Gap Bias"),
                 subtitle="",
                 get_value=lambda: f"{self._params.get_int(p + 'JerkDanger')}%",
                 on_click=lambda: self._show_slider(p + "JerkDanger", 25, 200, step=5, unit="%")),
      SettingRow(f"{p}JerkSpeedDec", "value", tr_noop("Slowdown Response"),
                 subtitle="",
                 get_value=lambda: f"{self._params.get_int(p + 'JerkSpeedDecrease')}%",
                 on_click=lambda: self._show_slider(p + "JerkSpeedDecrease", 25, 200, step=5, unit="%")),
      SettingRow(f"{p}JerkSpeed", "value", tr_noop("Speed-Up Response"),
                 subtitle="",
                 get_value=lambda: f"{self._params.get_int(p + 'JerkSpeed')}%",
                 on_click=lambda: self._show_slider(p + "JerkSpeed", 25, 200, step=5, unit="%")),
      SettingRow(f"{p}Reset", "action", tr_noop("Reset to Defaults"),
                 subtitle="",
                 action_text=tr_noop("Reset"),
                 action_danger=True,
                 on_click=lambda: self._reset_profile(p)),
    ])
    return rows

  def _build_weather_offsets_rows(self, suffix: str) -> list[SettingRow]:
    s = suffix
    return [
      SettingRow(f"Follow{s}", "value", tr_noop("Following Distance"),
                 subtitle="",
                 get_value=lambda: f"+{self._params.get_int('IncreaseFollowing' + s)}s",
                 on_click=lambda: self._show_slider("IncreaseFollowing" + s, 0, 3, step=0.5, unit="s")),
      SettingRow(f"StoppedDist{s}", "value", tr_noop("Stopped Distance"),
                 subtitle="",
                 get_value=lambda: f"+{self._params.get_int('IncreasedStoppedDistance' + s)} ft",
                 on_click=lambda: self._show_slider("IncreasedStoppedDistance" + s, 0, 10, unit=" ft")),
      SettingRow(f"ReduceAccel{s}", "value", tr_noop("Reduce Accel"),
                 subtitle="",
                 get_value=lambda: f"{self._params.get_int('ReduceAcceleration' + s)}%",
                 on_click=lambda: self._show_slider("ReduceAcceleration" + s, 0, 99, unit="%")),
      SettingRow(f"ReduceLateral{s}", "value", tr_noop("Reduce Curve Speed"),
                 subtitle="",
                 get_value=lambda: f"{self._params.get_int('ReduceLateralAcceleration' + s)}%",
                 on_click=lambda: self._show_slider("ReduceLateralAcceleration" + s, 0, 99, unit="%")),
    ]

  def _set_weather_key(self):
    options = ["ADD", "REMOVE"]

    def on_select(res):
      if res == DialogResult.CONFIRM and dialog.selection:
        if dialog.selection == "ADD":

          def on_key(res, text):
            if res == DialogResult.CONFIRM:
              self._params.put("WeatherAPIKey", text)

          self._keyboard.reset(min_text_size=1)
          self._keyboard.set_title(tr_noop("Weather API Key"), "")
          self._keyboard.set_text("")
          self._keyboard.set_callback(lambda result: on_key(result, self._keyboard.text))
          gui_app.push_widget(self._keyboard)
        elif dialog.selection == "REMOVE":

          def on_confirm(res):
            if res == DialogResult.CONFIRM:
              self._params.remove("WeatherAPIKey")

          gui_app.push_widget(ConfirmDialog(tr_noop("Remove API Key?"), tr_noop("Confirm"), callback=on_confirm))

    dialog = MultiOptionDialog(tr_noop("Weather API Key"), options, "ADD", callback=on_select)
    gui_app.push_widget(dialog)
