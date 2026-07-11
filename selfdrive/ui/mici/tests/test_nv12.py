import numpy as np
import pytest

from openpilot.selfdrive.ui.mici.onroad.nv12 import split_nv12_planes


def test_split_nv12_planes_handles_aligned_y_padding():
  stride = 8
  height = 4
  uv_offset = 40
  frame = np.arange(uv_offset + stride * (height // 2), dtype=np.uint8)

  y, u, v = split_nv12_planes(frame, uv_offset, stride, height)

  np.testing.assert_array_equal(y, np.arange(32, dtype=np.uint8))
  np.testing.assert_array_equal(u, np.array([[40, 42, 44, 46], [48, 50, 52, 54]], dtype=np.uint8))
  np.testing.assert_array_equal(v, np.array([[41, 43, 45, 47], [49, 51, 53, 55]], dtype=np.uint8))
  assert u.flags.c_contiguous
  assert v.flags.c_contiguous


@pytest.mark.parametrize(("stride", "height"), [(0, 4), (7, 4), (8, 3)])
def test_split_nv12_planes_rejects_invalid_dimensions(stride, height):
  with pytest.raises(ValueError):
    split_nv12_planes(np.zeros(64, dtype=np.uint8), 32, stride, height)


def test_split_nv12_planes_rejects_short_buffer():
  with pytest.raises(ValueError):
    split_nv12_planes(np.zeros(47, dtype=np.uint8), 32, 8, 4)
