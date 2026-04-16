#include "adapters/raylib_adapter.h"
#include "backends/imgui_impl_opengl3.h"
#include "demo_game/game_state.h"
#include "imgui.h"
#include "raylib.h"
#include "sim/tick.h"
#include "sim/world.h"

void imgui_setup();
void imgui_poll_io();
void imgui_draw(const sim::World& world);
void imgui_render();
void imgui_shutdown();
void render_player(const demo_game::PlayerState& player);
demo_game::PlayerInput poll_player_input();

sim::Scalar move_speed{1};

int main() {
  const int screen_width = 800;
  const int screen_height = 450;

  sim::World world;
  double accumulator = 0.0;

  InitWindow(screen_width, screen_height, "rewind engine demo app");

  imgui_setup();

  SetTargetFPS(60);

  demo_game::GameState game_state{};
  game_state.player.position = sim::Vec2(screen_width / 2, screen_height / 2);

  while (!WindowShouldClose()) {
    accumulator += static_cast<double>(GetFrameTime());
    if (accumulator > 0.25) {
      accumulator = 0.25;
    }

    const demo_game::PlayerInput input = poll_player_input();

    while (accumulator >= sim::kFixedDtSeconds) {
      world.tick();
      accumulator -= sim::kFixedDtSeconds;

      sim::Vec2 direction{input.move_x, input.move_y};
      direction.normalize();
      sim::Vec2 movement = direction * move_speed;
      game_state.player.position += movement;
    }

    imgui_poll_io();

    BeginDrawing();
    {
      ClearBackground(RAYWHITE);
      DrawText(TextFormat("World Tick Count: %llu",
                          static_cast<unsigned long long>(world.tick_count())),
               20, 20, 20, BLACK);
      DrawText(TextFormat("FPS: %i", GetFPS()), 20, 40, 20, BLACK);
      DrawText(TextFormat("Delta Time: %f", GetFrameTime()), 20, 60, 20, BLACK);

      render_player(game_state.player);

      // imgui_draw(world);
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
        ImGui::Text("move_x: %d", input.move_x);
        ImGui::Text("move_y: %d", input.move_y);
        ImGui::End();
      }

      imgui_render();
    }
    EndDrawing();
  }

  imgui_shutdown();

  CloseWindow();

  return 0;
}

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

void render_player(const demo_game::PlayerState& player) {
  DrawCircleV(client::adapters::to_vector2(player.position), 32, BLUE);
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

void imgui_draw(const sim::World& world) {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui::NewFrame();

  ImGui::Begin("Debug");
  ImGui::Text("tick: %llu",
              static_cast<unsigned long long>(world.tick_count()));
  ImGui::Text("fps: %d", GetFPS());
  ImGui::Text("frame dt: %.6f", GetFrameTime());
  ImGui::Text("tick rate: %u", sim::kTickRate);
  ImGui::End();
}

void imgui_render() {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void imgui_shutdown() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui::DestroyContext();
}
