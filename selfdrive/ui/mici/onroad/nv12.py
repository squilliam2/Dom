import numpy as np


def split_nv12_planes(frame_data: np.ndarray, uv_offset: int, stride: int, height: int) -> tuple[np.ndarray, np.ndarray, np.ndarray]:
  if stride <= 0 or height <= 0 or stride % 2 or height % 2:
    raise ValueError(f"invalid NV12 dimensions: stride={stride}, height={height}")

  y_size = stride * height
  uv_size = stride * (height // 2)
  uv_end = uv_offset + uv_size
  if uv_offset < y_size or uv_end > frame_data.size:
    raise ValueError(f"invalid NV12 layout: size={frame_data.size}, y_size={y_size}, uv_offset={uv_offset}, uv_end={uv_end}")

  y_data = frame_data[:y_size]
  uv_plane = frame_data[uv_offset:uv_end].reshape(height // 2, stride)
  u_data = np.ascontiguousarray(uv_plane[:, 0::2])
  v_data = np.ascontiguousarray(uv_plane[:, 1::2])
  return y_data, u_data, v_data
