#include "sim/vec2.h"

#include <cmath>

namespace sim {

std::int64_t integer_sqrt_same_platform(std::int64_t value) {
  if (value <= 0) return 0;

  std::int64_t x =
      static_cast<std::int64_t>(std::sqrt(static_cast<double>(value)));

  // Correct for float rounding (at most ±1 off for values <= 2^53)
  // For values > 2^53, double loses precision so we may need a wider correction
  while (x > 0 && x * x > value) --x;
  while ((x + 1) * (x + 1) <= value) ++x;

  return x;
}

std::int64_t integer_sqrt(std::int64_t value) {
  if (value <= 0) {
    return 0;
  }

  std::int64_t result = 0;
  std::int64_t bit = std::int64_t{1} << 62;

  while (bit > value) {
    bit >>= 2;
  }

  while (bit != 0) {
    if (value >= result + bit) {
      value -= result + bit;
      result = (result >> 1) + bit;
    } else {
      result >>= 1;
    }

    bit >>= 2;
  }

  return result;
}

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
