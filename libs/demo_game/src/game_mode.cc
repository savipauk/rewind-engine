#include "demo_game/game_mode.h"

#include "sim/world.h"

namespace demo_game {

int GameMode::max_players() const {
    sim::World world;
    (void)world.tick_count();
    return 2;
}

}  // namespace demo_game
