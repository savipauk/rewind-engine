#pragma once

#include <cstdint>

namespace sim {

inline constexpr std::uint32_t kTickRate = 128;
inline constexpr double kFixedDtSeconds = 1.0 / static_cast<double>(kTickRate);

constexpr std::uint32_t tick_rate() {
  return kTickRate;
}

}  // namespace sim
