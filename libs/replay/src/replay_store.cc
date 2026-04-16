#include "replay/replay_store.h"

#include "sim/world.h"

namespace replay {

void ReplayStore::clear() {
    sim::World world;
    (void)world.tick_count();
    frame_count_ = 0;
}

std::size_t ReplayStore::frame_count() const {
    return frame_count_;
}

}  // namespace replay
