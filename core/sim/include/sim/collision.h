#pragma once

#include "sim/shape.h"
namespace sim {

struct Contact {
  bool hit;
  Vec2 normal;
  Scalar penetration;
  Vec2 point;
};

bool intersects(Circle a, Circle b);
bool intersects(Circle c, Rect r);
bool intersects(Rect a, Rect b);

Contact contact(Circle a, Circle b);
Contact contact(Circle c, Rect r);
Contact contact(Rect a, Rect b);

}  // namespace sim
