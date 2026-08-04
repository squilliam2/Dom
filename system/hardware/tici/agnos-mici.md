# StarPilot Mici AGNOS image

This image is a byte-preserving patch of Dom AGNOS 12.8.28 for comma four.
Tici and Tizi continue to use `agnos.json` and Dom's original system image.

## Provenance

- Base version: `12.8.28`
- Base raw system SHA-256: `4c01245932068aedfceb41cb1aab1f7f044f6659aa2fe2de558f99e2d3aa5793`
- Patched version: `12.8.28-sq-mici.2`
- Patched raw system SHA-256: `83af277f7ffe1f91b3c6cfbd7cd9b61439c9117062f2c2ebbd7191c4dc453b91`
- Compressed archive SHA-256: `a4ad37c8d1b33a5fa24b9140d5ee7745a0c81b5d4bf62a9cc032e374e246092c`
- Compressed archive size: `929760684` bytes

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
that manager environment and starts in parallel with Weston, so it adds no
ordering dependency to the boot path. It uses the panel calibration already
shipped by Dom's image.

Dom's original Weston unit, kernel, firmware, hardware services, setup images,
and all openpilot driving and lateral-control files are unchanged.

## Selection and rollback

`launch_env.sh` selects `agnos-mici.json` only for `mici`. Older updaters still
see the unchanged public `AGNOS_VERSION=12.8.28`, preventing them from flashing
the Mici manifest before the new selector is running. Switching to a branch
that targets Dom AGNOS 12.8.28 restores the original image through the normal
A/B updater.
