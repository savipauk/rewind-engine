#include <chrono>
#include <print>
#include <thread>

#include "demo_game/game_state.h"
#include "net/channel.h"
#include "sim/tick.h"
#include "sim/world.h"

#define PORT 4000

int main() {
  sim::World world;
  double accumulator = 0.0;

  const int arena_width = 1280;
  const int arena_height = 720;

  demo_game::Game game = demo_game::construct_serverside(
      sim::Vec2(arena_width / 2, arena_height / 2));

  net::Channel channel;
  if (!channel.bind(PORT)) {
    std::println("Failed to bind UDP server socket");
    return 1;
  }

  bool running = true;
  auto last_time = std::chrono::steady_clock::now();

  std::println("Starting server at port {}...", PORT);
  while (running) {
    const auto now = std::chrono::steady_clock::now();
    const std::chrono::duration<double> frame_time = now - last_time;
    last_time = now;

    accumulator += frame_time.count();
    if (accumulator > 0.25) {
      accumulator = 0.25;
    }

    while (accumulator >= sim::kFixedDtSeconds) {
      world.tick();
      accumulator -= sim::kFixedDtSeconds;

      demo_game::PlayerInput input{0, 0};
      demo_game::step(game, input);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  return 0;
}
