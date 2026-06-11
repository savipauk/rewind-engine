#include "debug_ui.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"

namespace client {

void draw_debug(demo_game::Player& p) {
  scalar_slider("gravity", p.gravity, 0.0f, 0.5f);

  scalar_slider("air_x_accel", p.air_x_accel, 0.0f, 1.0f);
  scalar_slider("ground_x_accel", p.ground_x_accel, 0.0f, 1.0f);

  scalar_slider("air_y_accel", p.air_y_accel, 0.0f, 1.0f);
  scalar_slider("weak_air_y_accel", p.weak_air_y_accel, 0.0f, 0.5f);
  scalar_slider("ground_y_accel", p.ground_y_accel, 0.0f, 1.0f);

  scalar_slider("air_y_accel_loss", p.available_air_y_accel_loss, 0.0f, 0.2f);

  scalar_slider("horizontal_drag", p.horizontal_drag, 0.0f, 1.0f);

  scalar_slider("max_available_air_accel", p.max_available_air_accel, 0.0f,
                2.0f);
  scalar_slider("max_vertical_speed", p.max_vertical_speed, 0.0f, 20.0f);
  scalar_slider("max_vertical_speed_down", p.max_vertical_speed_down, 0.0f,
                30.0f);
  scalar_slider("max_horizontal_speed", p.max_horizontal_speed, 0.0f, 20.0f);
  scalar_slider("max_slope_angle", p.max_slope_angle, 0.0f, 2 * 3.14f);

  ImGui::Text("available_air_y_accel: %.2f",
              p.available_air_y_accel.to_double());
  ImGui::Text("velocity: (%.2f, %.2f)", p.velocity.x.to_double(),
              p.velocity.y.to_double());
  ImGui::Text("grounded: %d", p.grounded);
  ImGui::Text("hits_head: %d", p.hits_head);
}

void draw_debug(demo_game::Wall& wall) {
  (void)wall;
}

void draw_debug_ui(demo_game::Game& game, sim::World& world) {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui::NewFrame();

  ImGui::Begin("Debug");

  ImGui::Text("tick: %llu",
              static_cast<unsigned long long>(world.tick_count()));

  ImGui::Begin("Player");
  draw_debug(game.player);
  ImGui::End();

  ImGui::Begin("Walls");

  for (auto& wall : game.walls) {
    draw_debug(wall);
  }

  ImGui::End();
  ImGui::End();
}

bool scalar_slider(const char* label, sim::Scalar& value, float min,
                   float max) {
  float v = value.to_float();

  bool changed = ImGui::SliderFloat(label, &v, min, max);

  if (changed) {
    value = sim::Scalar(v);
  }

  return changed;
}

}  // namespace client
