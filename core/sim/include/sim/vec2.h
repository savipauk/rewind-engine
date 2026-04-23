#pragma once

#include "sim/scalar.h"

namespace sim {

struct Vec2 {
  sim::Scalar x{};
  sim::Scalar y{};

  Vec2() = default;

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

  Vec2(sim::Scalar x, sim::Scalar y) : x(x), y(y) {}

  Vec2& operator+=(const Vec2& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  Vec2 operator+(const Vec2& rhs) const {
    return Vec2{x + rhs.x, y + rhs.y};
  }

  Vec2& operator-=(const Vec2& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  Vec2 operator-(const Vec2& rhs) const {
    return Vec2{x - rhs.x, y - rhs.y};
  }

  Vec2& operator*=(sim::Scalar scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  Vec2 operator*(sim::Scalar scalar) const {
    return Vec2{x * scalar, y * scalar};
  }

  Scalar magnitude() const;
  Vec2 normalized() const;
  Vec2& normalize();
};

}  // namespace sim
