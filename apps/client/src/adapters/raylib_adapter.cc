#include "adapters/raylib_adapter.h"

namespace client::adapters {

Vector2 to_vector2(const sim::Vec2& value) {
  return Vector2{
      .x = value.x.to_float(),
      .y = value.y.to_float(),
  };
}

}  // namespace client::adapters
