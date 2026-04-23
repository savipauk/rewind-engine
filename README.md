# rewind-engine

`rewind-engine` is a deterministic rollback-capable multiplayer simulation framework in C++ with a minimal 2D arena demo used as a thin test workload.

The focus of the project is the engine and protocol work: deterministic simulation, rollback/resimulation, replay, and custom UDP reliability. The demo game exists to visualize and stress the system, not to grow into a feature-rich game.

The repository is still in an early bootstrap state. Some sections below describe the intended architecture and dependency stack, and should be updated as implementation lands.

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

## Planned Architecture

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

- Root CMake project exists
- `client` and `server` targets build
- a small smoke test exists
- the core engine systems are not implemented yet

## Intended Tech Stack

The current target stack is:

- C++23
- CMake + Ninja
- standalone Asio for networking
- raylib for the client window, rendering, and input
- Dear ImGui for debug UI and metrics overlays
- MessagePack or custom binary formats for replay/config serialization where appropriate

Note: dependency integration is still in progress. The repository structure is being prepared ahead of the full implementation.

## Getting Started

Expected prerequisites for the full project:

- CMake 3.28+
- Ninja
- a C++23 compiler
- Asio
- raylib
- Dear ImGui
- MessagePack

At the moment, not all external dependencies are wired into the build yet. The current bootstrap can still be configured and built with the existing CMake presets.

Configure and build a debug build:

```bash
cmake --preset debug
cmake --build --preset debug
```

Run tests:

```bash
ctest --preset debug
```

Current bootstrap executables print placeholder output:

- `client`
- `server`

## Roadmap

Implementation is expected to progress in this order:

1. Deterministic simulation core
2. UDP transport and custom reliability
3. Lockstep baseline
4. Rollback and resimulation
5. Replay, experiments, and evaluation support

Immediate next step:

- bootstrap a minimal raylib hello-world in `apps/client`
- begin the deterministic simulation foundation in parallel

## Status

This repository currently contains the scaffold for the project rather than the finished systems.

As new pieces land, this README should be updated so planned sections gradually turn into implemented status instead of staying aspirational.
