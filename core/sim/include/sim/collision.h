#pragma once

#include "sim/shape.h"
namespace sim {

struct Contact {
  bool hit;
  Vec2 normal;
  Scalar penetration;
  Vec2 point;
};

bool intercepts(Circle a, Circle b);
bool intercepts(Circle c, Rect r);
bool intercepts(Rect a, Rect b);

Contact contact(Circle a, Circle b);
Contact contact(Circle c, Rect r);
Contact contact(Rect a, Rect b);

}  // namespace sim
