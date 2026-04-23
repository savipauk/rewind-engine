#include "client_systems.h"

#include "adapters/raylib_adapter.h"
#include "raylib.h"

namespace client {

demo_game::PlayerInput poll_player_input() {
  demo_game::PlayerInput input{};

  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    input.move_x += 1;
  }
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    input.move_x -= 1;
  }

  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
    input.move_y += 1;
  }
  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
    input.move_y -= 1;
  }

  return input;
}

void render_game(const demo_game::Game& game) {
  DrawCircleV(client::adapters::to_vector2(game.player.position),
              game.player.radius.to_float(), BLUE);
}

}  // namespace client
