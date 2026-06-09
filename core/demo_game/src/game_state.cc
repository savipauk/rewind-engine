#include "demo_game/game_state.h"

#include <algorithm>

#include "sim/collision.h"

namespace demo_game {

Game make_initial_game(const sim::Vec2& player_start_position, int screen_width,
                       int screen_height) {
  Game game{};
  game.screen_width = screen_width;
  game.screen_height = screen_height;
  game.player.shape.position = player_start_position;

  int boundary_size = 16;
  game.walls.emplace_back(0, screen_height - boundary_size, screen_width,
                          boundary_size);
  game.walls.emplace_back(0, 0, screen_width, boundary_size);
  game.walls.emplace_back(0, 0, boundary_size, screen_height);
  game.walls.emplace_back(screen_width - boundary_size, 0, boundary_size,
                          screen_height);

  return game;
}

void step(Game& game, const PlayerInput& input) {
  Player& p = game.player;

  sim::Vec2 move_direction{input.move_x, input.move_y};
  move_direction.normalize();

  p.velocity.y += p.gravity;

  auto accel = p.air_acceleration;
  auto fric = p.air_friction;
  auto drag = p.horizontal_drag;

  if (p.grounded) {
    accel = p.ground_acceleration;
    fric = p.ground_friction;
    drag = p.horizontal_drag;
  }

  p.velocity += move_direction * accel;
  p.velocity *= fric;
  p.velocity.x *= drag;

  if (p.hits_head && p.velocity.y < 0) {
    p.velocity.y = 0;
  }

  p.velocity.x = std::clamp(p.velocity.x, p.max_horizontal_speed * -1,
                            p.max_horizontal_speed);
  p.velocity.y =
      std::clamp(p.velocity.y, p.max_fall_speed * -1, p.max_fall_speed);

  sim::Vec2 move_delta = p.velocity;

  sim::Circle temp_player = p.shape;

  const bool delta_x_is_zero = move_delta.x.value == 0;
  const bool delta_y_is_zero = move_delta.y.value == 0;

  if (!delta_x_is_zero) {
    temp_player.position.x += move_delta.x;
  }

  if (!delta_y_is_zero) {
    temp_player.position.y += move_delta.y;
  }

  if (!delta_x_is_zero || !delta_y_is_zero) {
    bool grounded = false;
    bool hits_head = false;
    for (const auto& wall : game.walls) {
      const sim::Contact c = sim::contact(temp_player, wall.shape);
      if (!c.hit) {
        continue;
      }

      if (!delta_x_is_zero && c.normal.x.value != 0) {
        temp_player.position.x -= c.normal.x * c.penetration;
      }

      if (!delta_y_is_zero && c.normal.y.value != 0) {
        if (c.normal.y > 0) {
          grounded = true;
        }
        if (c.normal.y < 0) {
          hits_head = true;
        }
        temp_player.position.y -= c.normal.y * c.penetration;
      }
    }
    p.grounded = grounded;
    p.hits_head = hits_head;
  }

  p.shape.position = temp_player.position;
}

void set_var(sim::Scalar* value, sim::Scalar new_value) {
  *value = new_value;
}

}  // namespace demo_game
