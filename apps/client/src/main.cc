#include <print>

#include "backends/imgui_impl_opengl3.h"
#include "client_systems.h"
#include "debug_ui.h"
#include "demo_game/game_state.h"
#include "demo_game/snapshot.h"
#include "imgui.h"
#include "raylib.h"
#include "rlgl.h"
#include "sim/snapshot.h"
#include "sim/tick.h"
#include "sim/world.h"

void imgui_setup();
void imgui_poll_io();
void imgui_render();
void imgui_shutdown();

int main() {
  const int screen_width = 1280;
  const int screen_height = 720;

  sim::World world;
  double accumulator = 0.0;

  InitWindow(screen_width, screen_height, "rewind engine demo app");

  imgui_setup();

  SetTargetFPS(144);

  demo_game::Game game = demo_game::make_initial_game(
      sim::Vec2(screen_width / 2, screen_height / 2), screen_width,
      screen_height);

  std::vector<std::byte> snapshot_buffer(4096);

  while (!WindowShouldClose()) {
    accumulator += static_cast<double>(GetFrameTime());
    if (accumulator > 0.25) {
      accumulator = 0.25;
    }

    const demo_game::PlayerInput input = client::poll_player_input();

    while (accumulator >= sim::kFixedDtSeconds) {
      world.tick();
      accumulator -= sim::kFixedDtSeconds;

      demo_game::step(game, input);
    }

    if (IsKeyPressed(KEY_R)) {
      std::println("Writing snapshot...");

      sim::SnapshotWriter writer{std::span<std::byte>(snapshot_buffer)};
      if (demo_game::write_snapshot(game, writer)) {
        const std::size_t used = writer.bytes_written();
        snapshot_buffer.resize(used);
        std::println("Successfully wrote snapshot.");
      } else {
        std::println("Failed to write snapshot");
      }
    }

    if (IsKeyPressed(KEY_L)) {
      std::println("Loading snapshot");
      sim::SnapshotReader reader{std::span<const std::byte>(snapshot_buffer)};

      if (demo_game::read_snapshot(game, reader)) {
        std::println("Successfully read snapshot.");
      } else {
        std::println("Failed to load snapshot");
      }
    }

    imgui_poll_io();

    BeginDrawing();
    {
      ClearBackground(RAYWHITE);

      client::render_game(game);

      DrawText(TextFormat("World Tick Count: %llu",
                          static_cast<unsigned long long>(world.tick_count())),
               20, 20, 20, BLACK);
      DrawText(TextFormat("FPS: %i", GetFPS()), 20, 40, 20, BLACK);
      DrawText(TextFormat("Delta Time: %f", GetFrameTime()), 20, 60, 20, BLACK);

      client::draw_debug_ui(game, world);

      rlDrawRenderBatchActive();
      imgui_render();
    }
    EndDrawing();
  }

  imgui_shutdown();

  CloseWindow();

  return 0;
}

void imgui_setup() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO& io = ImGui::GetIO();
  (void)io;

  ImGui::StyleColorsDark();
  ImGui_ImplOpenGL3_Init("#version 330");
}

void imgui_poll_io() {
  ImGuiIO& io = ImGui::GetIO();
  io.DisplaySize = ImVec2(static_cast<float>(GetScreenWidth()),
                          static_cast<float>(GetScreenHeight()));
  io.DeltaTime = GetFrameTime();

  const Vector2 mouse = GetMousePosition();
  io.MousePos = ImVec2(mouse.x, mouse.y);
  io.MouseDown[0] = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
  io.MouseDown[1] = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
  io.MouseDown[2] = IsMouseButtonDown(MOUSE_BUTTON_MIDDLE);

  const Vector2 wheel = GetMouseWheelMoveV();
  io.MouseWheel = wheel.y;
  io.MouseWheelH = wheel.x;

  io.AddKeyEvent(ImGuiKey_Escape, IsKeyDown(KEY_ESCAPE));
  io.AddKeyEvent(ImGuiKey_Space, IsKeyDown(KEY_SPACE));
  io.AddKeyEvent(ImGuiKey_LeftArrow, IsKeyDown(KEY_LEFT));
  io.AddKeyEvent(ImGuiKey_RightArrow, IsKeyDown(KEY_RIGHT));
  io.AddKeyEvent(ImGuiKey_UpArrow, IsKeyDown(KEY_UP));
  io.AddKeyEvent(ImGuiKey_DownArrow, IsKeyDown(KEY_DOWN));

  for (int c = GetCharPressed(); c > 0; c = GetCharPressed()) {
    io.AddInputCharacter(static_cast<unsigned int>(c));
  }
}

void imgui_render() {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void imgui_shutdown() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui::DestroyContext();
}
