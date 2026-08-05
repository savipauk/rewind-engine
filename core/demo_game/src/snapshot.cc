#include "demo_game/snapshot.h"

#include <cstdint>

#include "demo_game/game_state.h"
#include "sim/snapshot.h"

namespace demo_game {

// Player state is serialized field-by-field: writing the whole struct
// would also write padding bytes, which breaks byte-identical snapshots
// and any future checksum-based desync detection.

bool write_snapshot(const Game& game, sim::SnapshotWriter& writer) {
  const Player& p = game.player;

  if (!writer.write_pod(p.shape.position.x)) return false;
  if (!writer.write_pod(p.shape.position.y)) return false;
  if (!writer.write_pod(p.shape.radius)) return false;
  if (!writer.write_pod(p.velocity.x)) return false;
  if (!writer.write_pod(p.velocity.y)) return false;

  const std::uint8_t grounded = p.grounded ? 1 : 0;
  const std::uint8_t hits_head = p.hits_head ? 1 : 0;
  if (!writer.write_pod(grounded)) return false;
  if (!writer.write_pod(hits_head)) return false;

  if (!writer.write_pod(p.gravity)) return false;
  if (!writer.write_pod(p.air_x_accel)) return false;
  if (!writer.write_pod(p.ground_x_accel)) return false;
  if (!writer.write_pod(p.air_y_accel)) return false;
  if (!writer.write_pod(p.weak_air_y_accel)) return false;
  if (!writer.write_pod(p.ground_y_accel)) return false;
  if (!writer.write_pod(p.available_air_y_accel)) return false;
  if (!writer.write_pod(p.available_air_y_accel_loss)) return false;
  if (!writer.write_pod(p.horizontal_drag)) return false;
  if (!writer.write_pod(p.max_available_air_accel)) return false;
  if (!writer.write_pod(p.max_vertical_speed)) return false;
  if (!writer.write_pod(p.max_vertical_speed_down)) return false;
  if (!writer.write_pod(p.max_horizontal_speed)) return false;
  if (!writer.write_pod(p.min_ground_normal_y)) return false;

  auto write_wall = [&writer](const Wall& wall) {
    if (!writer.write_pod(wall.shape.min.x)) return false;
    if (!writer.write_pod(wall.shape.min.y)) return false;
    if (!writer.write_pod(wall.shape.max.x)) return false;
    if (!writer.write_pod(wall.shape.max.y)) return false;
    if (!writer.write_pod(wall.bounciness)) return false;
    return true;
  };

  if (!writer.write_vector(game.walls, write_wall)) return false;

  return true;
}

bool read_snapshot(Game& game, sim::SnapshotReader& reader) {
  Player& p = game.player;

  if (!reader.read_pod(p.shape.position.x)) return false;
  if (!reader.read_pod(p.shape.position.y)) return false;
  if (!reader.read_pod(p.shape.radius)) return false;
  if (!reader.read_pod(p.velocity.x)) return false;
  if (!reader.read_pod(p.velocity.y)) return false;

  std::uint8_t grounded = 0;
  std::uint8_t hits_head = 0;
  if (!reader.read_pod(grounded)) return false;
  if (!reader.read_pod(hits_head)) return false;
  p.grounded = grounded != 0;
  p.hits_head = hits_head != 0;

  if (!reader.read_pod(p.gravity)) return false;
  if (!reader.read_pod(p.air_x_accel)) return false;
  if (!reader.read_pod(p.ground_x_accel)) return false;
  if (!reader.read_pod(p.air_y_accel)) return false;
  if (!reader.read_pod(p.weak_air_y_accel)) return false;
  if (!reader.read_pod(p.ground_y_accel)) return false;
  if (!reader.read_pod(p.available_air_y_accel)) return false;
  if (!reader.read_pod(p.available_air_y_accel_loss)) return false;
  if (!reader.read_pod(p.horizontal_drag)) return false;
  if (!reader.read_pod(p.max_available_air_accel)) return false;
  if (!reader.read_pod(p.max_vertical_speed)) return false;
  if (!reader.read_pod(p.max_vertical_speed_down)) return false;
  if (!reader.read_pod(p.max_horizontal_speed)) return false;
  if (!reader.read_pod(p.min_ground_normal_y)) return false;

  auto read_wall = [&reader](Wall& wall) {
    if (!reader.read_pod(wall.shape.min.x)) return false;
    if (!reader.read_pod(wall.shape.min.y)) return false;
    if (!reader.read_pod(wall.shape.max.x)) return false;
    if (!reader.read_pod(wall.shape.max.y)) return false;
    if (!reader.read_pod(wall.bounciness)) return false;
    return true;
  };

  if (!reader.read_vector(game.walls, read_wall)) return false;

  return true;
}

}  // namespace demo_game
