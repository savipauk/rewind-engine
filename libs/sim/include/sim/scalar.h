#pragma once

#include <cstdint>

namespace sim {

struct Scalar {
  std::int64_t value;

  Scalar() {
    value = 0;
  }

  Scalar(float v) {
    value = static_cast<std::int64_t>(v * 100);
  }

  Scalar(double v) {
    value = static_cast<std::int64_t>(v * 100);
  }

  Scalar(int v) {
    value = static_cast<std::int64_t>(v * 100);
  }

  float to_float() const {
    return static_cast<float>(value) / 100.0f;
  }

  double to_double() const {
    return static_cast<double>(value) / 100.0;
  }
};

}  // namespace sim
