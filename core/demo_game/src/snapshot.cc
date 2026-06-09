#include "demo_game/snapshot.h"

namespace demo_game {

bool write_snapshot(const Game& game, sim::SnapshotWriter& writer) {
  (void)game;
  (void)writer;
  return true;
}

bool read_snapshot(Game& game, sim::SnapshotReader& reader) {
  (void)game;
  (void)reader;
  return true;
}

}  // namespace demo_game
