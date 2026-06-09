#include "backends/imgui_impl_opengl3.h"
#include "client_systems.h"
#include "demo_game/game_state.h"
#include "imgui.h"
#include "raylib.h"
#include "rlgl.h"
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

  float gravity = game.player.gravity.to_float();
  float air_acceleration = game.player.air_acceleration.to_float();
  float ground_acceleration = game.player.ground_acceleration.to_float();
  float air_friction = game.player.air_friction.to_float();
  float ground_friction = game.player.ground_friction.to_float();
  float horizontal_drag = game.player.horizontal_drag.to_float();
  float max_vertical_speed = game.player.max_vertical_speed.to_float();
  float max_horizontal_speed = game.player.max_horizontal_speed.to_float();

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

      // ImGui draw
      {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Debug");
        ImGui::Text("tick: %llu",
                    static_cast<unsigned long long>(world.tick_count()));
        ImGui::Text("fps: %d", GetFPS());
        ImGui::Text("frame dt: %.6f", GetFrameTime());
        ImGui::Text("tick rate: %u", sim::kTickRate);
        ImGui::Text("grounded: %d", game.player.grounded);
        ImGui::Text("move_x: %d", input.move_x);
        ImGui::Text("move_y: %d", input.move_y);
        ImGui::Text("pos: %d %d", game.player.shape.position.x.to_int(),
                    game.player.shape.position.y.to_int());
        ImGui::End();

        ImGui::Text("gravity: ");
        if (ImGui::SliderFloat("gravity", &gravity, 0.0f, 2.0f)) {
          demo_game::set_var(&game.player.gravity, sim::Scalar(gravity));
        }

        ImGui::Text("air_accel: ");
        if (ImGui::SliderFloat("air_accel", &air_acceleration, 0.1f, 5.0f)) {
          demo_game::set_var(&game.player.air_acceleration,
                             sim::Scalar(air_acceleration));
        }

        ImGui::Text("gnd_accel: ");
        if (ImGui::SliderFloat("gnd_accel", &ground_acceleration, 0.1f, 5.0f)) {
          demo_game::set_var(&game.player.ground_acceleration,
                             sim::Scalar(ground_acceleration));
        }

        ImGui::Text("air_fric: ");
        if (ImGui::SliderFloat("air_fric", &air_friction, 0.0f, 1.0f)) {
          demo_game::set_var(&game.player.air_friction,
                             sim::Scalar(air_friction));
        }

        ImGui::Text("gnd_fric: ");
        if (ImGui::SliderFloat("gnd_fric", &ground_friction, 0.0f, 1.0f)) {
          demo_game::set_var(&game.player.ground_friction,
                             sim::Scalar(ground_friction));
        }

        ImGui::Text("hor_drag: ");
        if (ImGui::SliderFloat("hor_drag", &horizontal_drag, 0.0f, 1.0f)) {
          demo_game::set_var(&game.player.horizontal_drag,
                             sim::Scalar(horizontal_drag));
        }

        ImGui::Text("max_v_s: ");
        if (ImGui::SliderFloat("max_v_s", &max_vertical_speed, 4.0f, 25.0f)) {
          demo_game::set_var(&game.player.max_vertical_speed,
                             sim::Scalar(max_vertical_speed));
        }

        ImGui::Text("max_h_s: ");
        if (ImGui::SliderFloat("max_h_s", &max_horizontal_speed, 4.0f, 15.0f)) {
          demo_game::set_var(&game.player.max_horizontal_speed,
                             sim::Scalar(max_horizontal_speed));
        }
      }
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
