#pragma once

#include "sim/vec2.h"

namespace demo_game {

struct PlayerInput {
  int move_x{};
  int move_y{};
};

struct Player {
  sim::Vec2 position{};
  sim::Scalar move_speed{1};
  sim::Scalar radius{24};
  sim::Scalar gravity{1.5};

  sim::Scalar max_grav_speed{10};
};

struct Wall {
  int x;
  int y;
  int width;
  int height;
  sim::Scalar bounciness;
};

struct Game {
  Player player{};
};

Game make_initial_game(const sim::Vec2& player_start_position);
void set_player_move_speed(Game& game, sim::Scalar move_speed);
void step(Game& game, const PlayerInput& input);

}  // namespace demo_game
