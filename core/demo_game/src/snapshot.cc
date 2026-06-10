#include "demo_game/snapshot.h"

#include "demo_game/game_state.h"

namespace demo_game {

bool write_snapshot(const Game& game, sim::SnapshotWriter& writer) {
  if (!writer.write_pod(game.player)) return false;

  // auto write_wall = [&writer](const Wall& wall) {
  //   if (!writer.write_pod(wall.shape.min.x)) return false;
  //   if (!writer.write_pod(wall.shape.min.y)) return false;
  //   if (!writer.write_pod(wall.shape.max.x)) return false;
  //   if (!writer.write_pod(wall.shape.max.y)) return false;
  //   return true;
  // };
  //
  // if (!writer.write_vector(game.walls, write_wall)) return false;
  //
  return true;
}

bool read_snapshot(Game& game, sim::SnapshotReader& reader) {
  if (!reader.read_pod(game.player)) return false;

  // auto read_wall = [&reader](const Wall& wall) {
  //   if (!reader.read_pod(wall.shape.min.x)) return false;
  //   if (!reader.read_pod(wall.shape.min.y)) return false;
  //   if (!reader.read_pod(wall.shape.max.x)) return false;
  //   if (!reader.read_pod(wall.shape.max.y)) return false;
  //   return true;
  // };
  //
  // if (!reader.read_vector(game.walls, read_wall)) return false;
  //
  return true;
}

}  // namespace demo_game
