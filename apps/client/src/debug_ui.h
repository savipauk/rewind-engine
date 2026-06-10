#pragma once

#include "demo_game/game_state.h"
#include "sim/world.h"

namespace client {

void draw_debug_ui(demo_game::Game& game, sim::World& world);

bool scalar_slider(const char* label, sim::Scalar& value, float min, float max);
void draw_debug(demo_game::Player& player);
void draw_debug(demo_game::Wall& wall);

}  // namespace client
