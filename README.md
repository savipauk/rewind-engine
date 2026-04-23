# rewind-engine

`rewind-engine` is a deterministic rollback-capable multiplayer simulation framework in C++ with a minimal 2D arena demo used as a thin test workload.

The focus of the project is the engine and protocol work: deterministic simulation, rollback/resimulation, replay, and custom UDP reliability. The demo game exists to visualize and stress the system, not to grow into a feature-rich game.

The repository is still in active development. Some sections below describe target architecture and planned milestones, while implemented pieces are called out explicitly.

## Goals

- Deterministic fixed-tick simulation
- Snapshot, restore, rollback, and resimulation
- Replay recording with periodic checkpoints
- Custom UDP packet protocol with reliability on top
- Clear separation between deterministic core code and frontend code
- A minimal 2D arena demo for evaluation and debugging

## Non-goals

- A polished or content-heavy game
- 3D support
- Heavy middleware or external physics engines
- Asset pipelines, matchmaking, cosmetics, anti-cheat, or large-scale product systems
- Over-generalizing the engine for hypothetical future use cases

## Architecture

The project is organized around reusable engine modules first:

- `core/common` - shared utilities, logging, buffers, hashes, and low-level helpers
- `core/sim` - deterministic world state, fixed-tick stepping, snapshots, rollback helpers, state hashing
- `core/net` - UDP transport, packet headers, ack/sequence handling, resend logic, network simulation
- `core/replay` - replay logging, input timeline storage, checkpoints, playback and seeking
- `core/demo_game` - minimal arena rules and other game-specific logic
- `apps/server` - headless authoritative runtime
- `apps/client` - rendering, input capture, prediction, rollback orchestration, debug overlays
- `tests` - smoke, module, and integration coverage

Current bootstrap status:

- Root CMake project and presets exist (`debug`, `release`)
- `client` builds and runs a raylib + ImGui demo loop (rendering, input polling, fixed-tick stepping)
- `server` builds and currently prints `server bootstrap`
- Core modules are scaffolded and partially implemented (`common`, `sim`, `net`, `replay`, `demo_game`)
- Test coverage currently includes smoke and simulation collision tests

## Tech Stack

The current stack is:

- C++23
- CMake + Ninja
- raylib for the client window, rendering, and input (vendored under `external/raylib`)
- Dear ImGui for debug UI and metrics overlays (vendored under `external/imgui`)
- standalone Asio for networking (planned integration)
- MessagePack or custom binary formats for replay/config serialization where appropriate (planned)

Note: dependencies required by the current client build are already wired into CMake via vendored sources.

## Getting Started

Prerequisites:

- CMake 3.28+
- Ninja
- a C++23 compiler
- Xcode command line tools on macOS (or equivalent platform toolchain/OpenGL dependencies)

Configure and build a debug build:

```bash
cmake --preset debug
cmake --build --preset debug
```

Run tests:

```bash
ctest --preset debug
```

Run executables from a debug build:

```bash
./build/debug/apps/client/client
./build/debug/apps/server/server
```

Current runtime behavior:

- `client` opens the demo window and runs the fixed-tick simulation/render loop with a small ImGui debug panel
- `server` currently prints `server bootstrap`

## Roadmap

Implementation is expected to progress in this order:

1. Deterministic simulation core
2. UDP transport and custom reliability
3. Lockstep baseline
4. Rollback and resimulation
5. Replay, experiments, and evaluation support

## Status

This repository currently contains the scaffold for the project rather than the finished systems.

As new pieces land, this README should be updated so planned sections gradually turn into implemented status instead of staying aspirational.
