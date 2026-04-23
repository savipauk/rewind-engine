#pragma once

#include <cstdint>

namespace sim {

inline constexpr std::int64_t kScalarScale = 1000;

struct Scalar {
  std::int64_t value{0};

  Scalar() = default;

  Scalar(float v) {
    value = static_cast<std::int64_t>(v * kScalarScale);
  }

  Scalar(double v) {
    value = static_cast<std::int64_t>(v * kScalarScale);
  }

  Scalar(int v) {
    value = static_cast<std::int64_t>(v) * kScalarScale;
  }

  Scalar& operator+=(const Scalar& rhs) {
    value += rhs.value;
    return *this;
  }

  Scalar operator+(const Scalar& rhs) const {
    return Scalar::from_raw(value + rhs.value);
  }

  Scalar& operator-=(const Scalar& rhs) {
    value -= rhs.value;
    return *this;
  }

  Scalar operator-(const Scalar& rhs) const {
    return Scalar::from_raw(value - rhs.value);
  }

  Scalar& operator*=(const Scalar& rhs) {
    value = (value * rhs.value) / kScalarScale;
    return *this;
  }

  Scalar operator*(const Scalar& rhs) const {
    return Scalar::from_raw((value * rhs.value) / kScalarScale);
  }

  static Scalar from_raw(std::int64_t raw_value) {
    Scalar scalar;
    scalar.value = raw_value;
    return scalar;
  }

  float to_float() const {
    return static_cast<float>(value) / static_cast<float>(kScalarScale);
  }

  double to_double() const {
    return static_cast<double>(value) / static_cast<double>(kScalarScale);
  }
};

}  // namespace sim
