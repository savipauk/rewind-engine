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

  sim::Scalar air_x_accel{0.28};
  sim::Scalar ground_x_accel{0.28};

  sim::Scalar air_y_accel{0.2};
  sim::Scalar weak_air_y_accel{0.06};
  sim::Scalar ground_y_accel{0.28};
  sim::Scalar available_air_y_accel{1.0};
  sim::Scalar available_air_y_accel_loss{0.03};

  sim::Scalar horizontal_drag{0.96};

  sim::Scalar max_available_air_accel{1.0};
  sim::Scalar max_vertical_speed{6};
  sim::Scalar max_vertical_speed_down{15};
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

}  // namespace demo_game
