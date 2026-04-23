#include "demo_game/game_state.h"

namespace demo_game {

Game make_initial_game(const sim::Vec2& player_start_position) {
  Game game{};
  game.player.position = player_start_position;
  return game;
}

void set_player_move_speed(Game& game, sim::Scalar move_speed) {
  game.player.move_speed = move_speed;
}

void step(Game& game, const PlayerInput& input) {
  Player& p = game.player;

  sim::Vec2 direction{input.move_x, input.move_y};
  direction.normalize();
  const sim::Vec2 movement = direction * p.move_speed;
  p.position += movement;
}

}  // namespace demo_game
