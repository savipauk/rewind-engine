#pragma once

#include "raylib.h"
#include "sim/vec2.h"

namespace client::adapters {

Vector2 to_vector2(const sim::Vec2& value);

}  // namespace client::adapters
