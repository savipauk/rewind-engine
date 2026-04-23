#pragma once

#include "sim/scalar.h"
#include "sim/vec2.h"

namespace sim {

struct Circle {
  Vec2 position{};
  Scalar radius{};

  Circle() = default;

  Circle(Vec2 position, Scalar radius) {
    this->position = Vec2(position);
    this->radius = Scalar(radius);
  }
};

struct Rect {
  Vec2 min{};
  Vec2 max{};

  Rect() = default;

  Rect(Vec2 min, Vec2 max) {
    this->min = Vec2(min);
    this->max = Vec2(max);
  }
};

}  // namespace sim
