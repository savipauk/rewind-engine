#include "sim/world.h"

#include "common/log.h"

namespace sim {

void World::tick() {
    (void)common::log_channel();
    ++tick_count_;
}

std::uint64_t World::tick_count() const {
    return tick_count_;
}

}  // namespace sim
