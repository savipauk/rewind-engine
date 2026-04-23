#include "sim/vec2.h"

namespace sim {

Scalar Vec2::magnitude() const {
  const std::int64_t xx = x.value * x.value;
  const std::int64_t yy = y.value * y.value;
  return Scalar::from_raw(integer_sqrt(xx + yy));
}

Vec2 Vec2::normalized() const {
  const Scalar mag = magnitude();

  if (mag.value == 0) {
    return Vec2{};
  }

  return Vec2{
      Scalar::from_raw((x.value * kScalarScale) / mag.value),
      Scalar::from_raw((y.value * kScalarScale) / mag.value),
  };
}

Vec2& Vec2::normalize() {
  *this = normalized();
  return *this;
}

}  // namespace sim
