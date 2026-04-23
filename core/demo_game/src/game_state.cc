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

  sim::Circle candidate = p.shape;

  if (delta.x.value != 0) {
    candidate.position.x += delta.x;
    for (const auto& wall : game.walls) {
      const sim::Contact c = sim::contact(candidate, wall.shape);
      if (!c.hit || c.normal.x.value == 0) {
        continue;
      }
      candidate.position.x -= c.normal.x * c.penetration;
    }
  }

  if (delta.y.value != 0) {
    candidate.position.y += delta.y;
    for (const auto& wall : game.walls) {
      const sim::Contact c = sim::contact(candidate, wall.shape);
      if (!c.hit || c.normal.y.value == 0) {
        continue;
      }
      candidate.position.y -= c.normal.y * c.penetration;
    }
  }

  p.shape.position = candidate.position;
}

}  // namespace demo_game
