#pragma once

#include <cstdint>

namespace sim {

class World {
 public:
  void tick();
  std::uint64_t tick_count() const;

 private:
  std::uint64_t tick_count_{0};
};

}  // namespace sim
