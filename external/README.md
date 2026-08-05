# External Dependencies

This directory tracks third-party dependencies used by `rewind-engine`.

## Current Local Dependencies

The following libraries are currently vendored as git submodules:

- `external/raylib` - client-side windowing, input, and rendering
- `external/imgui` - debug UI and in-engine tooling overlays

Clone submodules after cloning the repository:

```bash
git submodule update --init --recursive
```

## System Dependencies

- `Asio` (standalone) - networking transport; found via a system install
  (e.g. Homebrew) in `core/net/CMakeLists.txt`, not vendored here

## Planned Additional Dependencies

These are still expected, but are not yet wired into the build:

- `MessagePack` - replay/config serialization when appropriate

## Notes

- The deterministic core should remain independent of `raylib` and `imgui`.
- Client-facing code may depend on `raylib` and `imgui`.
- If more third-party code is added here, keep this file updated so the dependency state stays accurate.
