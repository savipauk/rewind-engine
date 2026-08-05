#pragma once

#include <cstdint>

namespace sim {

// Fixed-point scale: 1 world unit == 1000 raw units (resolution 0.001).
//
// Range and precision assumptions:
// - Raw storage is int64. Multiplication computes a.value * b.value before
//   rescaling, so it overflows (UB) once |a * b| exceeds ~9.2e12 world
//   units^2; keep multiplication operands below ~3.0e6 world units.
// - Squared-distance helpers (Vec2::magnitude, collision) square raw
//   components, limiting safe coordinates to roughly +/-2.1e6 world units.
// - World/arena coordinates should stay well inside these bounds.
inline constexpr std::int64_t kScalarScale = 1000;

std::int64_t integer_sqrt_same_platform(std::int64_t value);
std::int64_t integer_sqrt(std::int64_t value);

struct Scalar {
  std::int64_t value{0};

  Scalar() = default;

  // Lossy float conversions are explicit so they stay visible at call
  // sites; they belong at rendering/debug boundaries, not in step logic.
  explicit Scalar(float v) {
    value = static_cast<std::int64_t>(v * kScalarScale);
  }

  explicit Scalar(double v) {
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

  bool operator==(const Scalar& rhs) const {
    return value == rhs.value;
  }

  bool operator!=(const Scalar& rhs) const {
    return value != rhs.value;
  }

  bool operator<(const Scalar& rhs) const {
    return value < rhs.value;
  }

  bool operator<=(const Scalar& rhs) const {
    return value <= rhs.value;
  }

  bool operator>(const Scalar& rhs) const {
    return value > rhs.value;
  }

  bool operator>=(const Scalar& rhs) const {
    return value >= rhs.value;
  }

  static Scalar from_raw(std::int64_t raw_value) {
    Scalar scalar;
    scalar.value = raw_value;
    return scalar;
  }

  int to_int() const {
    return static_cast<int>(value / kScalarScale);
  }

  float to_float() const {
    return static_cast<float>(value) / static_cast<float>(kScalarScale);
  }

  double to_double() const {
    return static_cast<double>(value) / static_cast<double>(kScalarScale);
  }
};

}  // namespace sim
