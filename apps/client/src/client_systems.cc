#include "client_systems.h"

#include "adapters/raylib_adapter.h"
#include "demo_game/game_state.h"
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
  DrawCircleV(client::adapters::to_vector2(game.player.shape.position),
              game.player.shape.radius.to_float(), BLUE);

  for (const demo_game::Wall& w : game.walls) {
    sim::Scalar width = w.shape.max.x - w.shape.min.x;
    sim::Scalar height = w.shape.max.y - w.shape.min.y;
    DrawRectangle(w.shape.min.x.to_int(), w.shape.min.y.to_int(),
                  width.to_int(), height.to_int(), BLACK);
  }
}

}  // namespace client
