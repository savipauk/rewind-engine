#pragma once

#include "sim/vec2.h"

namespace demo_game {

struct PlayerInput {
  int move_x;
  int move_y;
};

struct PlayerState {
  sim::Vec2 position{};
};

struct GameState {
  PlayerState player{};
};

}  // namespace demo_game
