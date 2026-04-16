#pragma once

#include "sim/scalar.h"

namespace sim {

struct Vec2 {
  sim::Scalar x{};
  sim::Scalar y{};

  Vec2() {}

  Vec2(float x, float y) {
    this->x = Scalar(x);
    this->y = Scalar(y);
  }

  Vec2(double x, double y) {
    this->x = Scalar(x);
    this->y = Scalar(y);
  }

  Vec2(int x, int y) {
    this->x = Scalar(x);
    this->y = Scalar(y);
  }
};

}  // namespace sim
