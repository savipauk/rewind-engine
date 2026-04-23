#pragma once

#include "sim/vec2.h"

namespace demo_game {

struct PlayerInput {
  int move_x;
  int move_y;
};

struct Player {
  sim::Vec2 position{};

  void process_input();
  void update();
  void render();
};

struct Game {
  Player player{};
};

}  // namespace demo_game
