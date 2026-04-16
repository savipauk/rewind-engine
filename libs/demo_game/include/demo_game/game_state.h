#pragma once

#include "sim/vec2.h"

namespace demo_game {

struct PlayerState {
  sim::Vec2 position{};
};

struct GameState {
  PlayerState player{};
};

}  // namespace demo_game
