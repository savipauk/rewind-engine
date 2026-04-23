#pragma once

#include "demo_game/game_state.h"

namespace client {

demo_game::PlayerInput poll_player_input();
void render_game(const demo_game::Game& game);

}  // namespace client
