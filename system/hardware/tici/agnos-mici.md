# Comma four AGNOS selection

Comma four uses the official AGNOS 18.5 partition set and display stack used by
sunnypilot. Its system image adds only the runtime compatibility files required
by StarPilot's existing binaries and optional processes. Comma 3 and comma 3X
continue to use Dom's original `agnos.json` and custom AGNOS.

## Provenance

- Manifest source: `sunnypilot/master:openpilot/common/hardware/tici/agnos.json`
- Manifest blob: `f22a57db75592dfcd119d3c2f443d6afeb1aed91`
- Official raw system SHA-256: `a396dd98ffd49614fb198d1b022a0c7a6d0a1e563c20ce11b0a975105ab50724`
- Compatible system version: `18.5-sq-mici.2`
- Compatible raw system SHA-256: `47c5539a9ab6027d5a4265dabef16339cd5eecae4f67589f23e85881f2b96538`
- Compressed asset SHA-256: `0d20e3f273be1e3cebba9ff64ad89b9d4218abd6336105d2deffaebb8b46ace6`

The official sparse image, official expanded filesystem, compatible raw image,
and decompressed release asset were independently hashed. A filesystem delta
audit found only `/VERSION`, these ten native compatibility entries, and the
Python packages listed below:

- `libkj-1.0.2.so`
- `libcapnp-1.0.2.so`
- `libavcodec.so.58` and `libavcodec.so.58.54.100`
- `libavformat.so.58` and `libavformat.so.58.29.100`
- `libavutil.so.56` and `libavutil.so.56.31.100`
- `libswresample.so.3` and `libswresample.so.3.5.100`

The added Python packages restore Dom features absent from the stock image:
OpenCV 4.11, ONNX 1.18, protobuf 6.31, and PyAudio 0.2.14. Existing stock
Python packages, including Raylib 6.0, are not overwritten. All 167 Raylib APIs
used by StarPilot were checked against that stock package.

The image retains the official Mici screen calibration service and matching
display stack. Runtime-loader checks cover camerad, loggerd, encoderd, bootlog,
pandad, the model extension, params, and msgq.

## Scope

`launch_env.sh` selects `agnos-mici.json` only when the physical device-tree
model is exactly `comma mici`. No custom display services, panel commands, or
color corrections are layered on top. Tici and Tizi retain Dom's complete
firmware and userspace partition set.
