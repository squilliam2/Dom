# StarPilot Mici AGNOS image

This image is a byte-preserving patch of Dom AGNOS 12.8.28 for comma four.
Tici and Tizi continue to use `agnos.json` and Dom's original system image.

## Provenance

- Base version: `12.8.28`
- Base raw system SHA-256: `4c01245932068aedfceb41cb1aab1f7f044f6659aa2fe2de558f99e2d3aa5793`
- Patched version: `12.8.28-sq-mici.1`
- Patched raw system SHA-256: `14ff858e40e4a2df0883f8029ae649ea069d302e5ceef59e483230c87b7e2361`
- Compressed archive SHA-256: `930cc40d81ec8963b537f35672a0477deef5fc34286a71fc7e88536fa77e743d`
- Compressed archive size: `1181703916` bytes

## Image changes

The full source and patched filesystems were compared with content checksums,
ownership, permissions, hard links, ACLs, and extended attributes. Only these
content changes exist:

- `/VERSION`
- `/usr/lib/systemd/system-environment-generators/40-starpilot-mici-color`
- `/usr/lib/systemd/system/starpilot-mici-screen-calibration.service`
- `/usr/lib/systemd/system/weston.service.d/40-starpilot-mici-display.conf`

The generator exports `DISABLE_COLOR_CORRECTION=1` only when the physical
device-tree model is exactly `comma mici`. The calibration service is gated by
that manager environment, applies `/usr/comma/screen_calibration.py` before
Weston, and uses the panel calibration already shipped by Dom's image.

Dom's original Weston unit, kernel, firmware, hardware services, setup images,
and all openpilot driving and lateral-control files are unchanged.

## Selection and rollback

`launch_env.sh` selects `agnos-mici.json` only for `mici`. Older updaters still
see the unchanged public `AGNOS_VERSION=12.8.28`, preventing them from flashing
the Mici manifest before the new selector is running. Switching to a branch
that targets Dom AGNOS 12.8.28 restores the original image through the normal
A/B updater.
