#include "demo_game/game_state.h"

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

void set_player_move_speed(Game& game, sim::Scalar move_speed) {
  game.player.move_speed = move_speed;
}

void step(Game& game, const PlayerInput& input) {
  Player& p = game.player;

  sim::Vec2 direction{input.move_x, input.move_y};
  direction.normalize();
  const sim::Vec2 delta = direction * p.move_speed;

  sim::Circle temp_player = p.shape;

  bool delta_x_is_zero = delta.x.value == 0;
  bool delta_y_is_zero = delta.y.value == 0;

  if (!delta_x_is_zero) {
    temp_player.position.x += delta.x;
  }

  if (!delta_y_is_zero) {
    temp_player.position.y += delta.y;
  }

  for (const auto& wall : game.walls) {
    const sim::Contact c = sim::contact(temp_player, wall.shape);
    if (!c.hit) {
      continue;
    }

    if (c.normal.y.value != 0) {
      temp_player.position.y -= c.normal.y * c.penetration;
    }

    if (c.normal.x.value != 0) {
      temp_player.position.x -= c.normal.x * c.penetration;
    }
  }

  p.shape.position = temp_player.position;
}

}  // namespace demo_game
