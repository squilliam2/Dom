"""Mici CameraView with deterministic NV12 color conversion."""

from openpilot.selfdrive.ui.onroad.cameraview import CameraView as SharedCameraView


class CameraView(SharedCameraView):
  # StarPilot's custom AGNOS can apply the wrong implicit YUV conversion to
  # EGL-imported camera buffers. The texture-copy path performs the camera's
  # declared BT.601 full-range conversion explicitly in the frame shader.
  _force_texture_copy = True
  _use_upstream_engaged_color = False


__all__ = ["CameraView"]
