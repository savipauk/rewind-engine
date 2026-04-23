#pragma once

#include <vector>

#include "sim/shape.h"
#include "sim/vec2.h"

namespace demo_game {

struct PlayerInput {
  int move_x{};
  int move_y{};
};

struct Player {
  sim::Circle shape{{}, 24};

  sim::Scalar move_speed{3};
  sim::Scalar gravity{1.5};

  sim::Scalar max_grav_speed{10};
};

struct Wall {
  sim::Rect shape{{}, {}};
  // sim::Scalar bounciness{1};
  Wall(int x, int y, int width, int height) {
    shape.min = {x, y};
    shape.max = {x + width, y + height};
  }
};

struct Game {
  int screen_width;
  int screen_height;

  Player player{};
  std::vector<Wall> walls;
};

Game make_initial_game(const sim::Vec2& player_start_position, int screen_width,
                       int screen_height);
void set_player_move_speed(Game& game, sim::Scalar move_speed);
void step(Game& game, const PlayerInput& input);

}  // namespace demo_game
