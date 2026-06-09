#pragma once

#include "demo_game/game_state.h"
#include "sim/snapshot.h"

namespace demo_game {

bool write_snapshot(const Game& game, sim::SnapshotWriter& writer);
bool read_snapshot(Game& game, sim::SnapshotReader& reader);

}  // namespace demo_game
