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
  sim::Vec2 velocity;

  // sticky bools, they reflect the last frame state instead of the current
  bool grounded{true};
  bool hits_head{false};

  sim::Scalar gravity{0.09};
  sim::Scalar air_acceleration{0.2};
  sim::Scalar ground_acceleration{0.28};
  sim::Scalar air_friction{0.99};     // Unused
  sim::Scalar ground_friction{0.85};  // Unused
  sim::Scalar horizontal_drag{0.96};

  sim::Scalar max_vertical_speed{6};
  sim::Scalar max_horizontal_speed{6};
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
void step(Game& game, const PlayerInput& input);

void set_var(sim::Scalar* value, sim::Scalar new_value);

}  // namespace demo_game
