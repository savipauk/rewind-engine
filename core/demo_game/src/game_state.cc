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

  game.walls.emplace_back(0, 3 * screen_height / 4, screen_width / 2,
                          boundary_size);
  game.walls.emplace_back(0, screen_height / 2, screen_width / 4,
                          boundary_size);

  return game;
}

void step(Game& game, const PlayerInput& input) {
  Player& p = game.player;

  sim::Vec2 move_direction{input.move_x, input.move_y};

  p.velocity.y += p.gravity;

  auto x_accel = p.air_x_accel;
  auto y_accel = p.air_y_accel;
  auto drag = p.horizontal_drag;

  if (p.grounded) {
    x_accel = p.ground_x_accel;
    y_accel = p.ground_y_accel;
  }

  if (move_direction.y < 0) {
    if (p.available_air_y_accel > 0) {
      p.velocity.y += move_direction.y * y_accel;
      p.available_air_y_accel -= p.available_air_y_accel_loss;
    } else {
      p.velocity.y += move_direction.y * p.weak_air_y_accel;
    }
  } else {
    p.velocity.y += move_direction.y * y_accel;
  }
  p.velocity.x += move_direction.x * x_accel;

  p.velocity.x *= drag;

  p.velocity.x = std::clamp(p.velocity.x, p.max_horizontal_speed * -1,
                            p.max_horizontal_speed);
  p.velocity.y = std::clamp(p.velocity.y, p.max_vertical_speed * -1,
                            p.max_vertical_speed_down);

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

        if (c.normal.x != 0) {
          p.velocity.x = 0;
        }
      }

      if (!delta_y_is_zero && c.normal.y.value != 0) {
        if (c.normal.y > 0) {
          grounded = true;
          p.available_air_y_accel = p.max_available_air_accel;
          if (p.velocity.y > 0) {
            p.velocity.y = 0;
          }
        }

        if (c.normal.y < 0) {
          hits_head = true;
          if (p.velocity.y < 0) {
            p.velocity.y = 0;
          }
        }
        temp_player.position.y -= c.normal.y * c.penetration;
      }
    }
    p.grounded = grounded;
    p.hits_head = hits_head;
  }

  p.shape.position = temp_player.position;
}

}  // namespace demo_game
