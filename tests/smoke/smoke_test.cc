#include <cassert>

#include "sim/world.h"

int main() {
    sim::World world;
    world.tick();
    assert(world.tick_count() == 1);
    return 0;
}
