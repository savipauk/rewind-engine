#include "sim/collision.h"

#include <algorithm>
#include <cstdint>

#include "sim/scalar.h"

namespace sim {
namespace {

Scalar scalar_min(Scalar lhs, Scalar rhs) {
  return lhs.value < rhs.value ? lhs : rhs;
}

Scalar scalar_max(Scalar lhs, Scalar rhs) {
  return lhs.value > rhs.value ? lhs : rhs;
}

std::int64_t clamp_raw(std::int64_t value, std::int64_t min, std::int64_t max) {
  return std::max(min, std::min(value, max));
}

Scalar distance_between(const Vec2& a, const Vec2& b) {
  const std::int64_t dx = b.x.value - a.x.value;
  const std::int64_t dy = b.y.value - a.y.value;
  return Scalar::from_raw(integer_sqrt(dx * dx + dy * dy));
}

Vec2 normalized_direction_or_default(const Vec2& direction,
                                     const Vec2& fallback) {
  Vec2 normal = direction;
  normal.normalize();
  if (normal.x.value == 0 && normal.y.value == 0) {
    return fallback;
  }
  return normal;
}

Scalar overlap_amount(Scalar min_a, Scalar max_a, Scalar min_b, Scalar max_b) {
  const Scalar lower_max = scalar_min(max_a, max_b);
  const Scalar upper_min = scalar_max(min_a, min_b);
  return lower_max - upper_min;
}

}  // namespace

bool intersects(Circle a, Circle b) {
  const std::int64_t dx = b.position.x.value - a.position.x.value;
  const std::int64_t dy = b.position.y.value - a.position.y.value;
  const std::int64_t radius_sum = a.radius.value + b.radius.value;
  return (dx * dx + dy * dy) <= (radius_sum * radius_sum);
}

bool intersects(Circle c, Rect r) {
  const std::int64_t closest_x =
      clamp_raw(c.position.x.value, r.min.x.value, r.max.x.value);
  const std::int64_t closest_y =
      clamp_raw(c.position.y.value, r.min.y.value, r.max.y.value);

  const std::int64_t dx = c.position.x.value - closest_x;
  const std::int64_t dy = c.position.y.value - closest_y;
  const std::int64_t radius = c.radius.value;

  return (dx * dx + dy * dy) <= (radius * radius);
}

bool intersects(Rect a, Rect b) {
  if (a.max.x.value < b.min.x.value || b.max.x.value < a.min.x.value) {
    return false;
  }
  if (a.max.y.value < b.min.y.value || b.max.y.value < a.min.y.value) {
    return false;
  }
  return true;
}

Contact contact(Circle a, Circle b) {
  Contact result{};
  result.hit = intersects(a, b);
  if (!result.hit) {
    return result;
  }

  const Vec2 direction = b.position - a.position;
  result.normal = normalized_direction_or_default(direction, Vec2{1, 0});

  const Scalar distance = distance_between(a.position, b.position);
  const Scalar radius_sum = a.radius + b.radius;
  result.penetration = radius_sum - distance;
  result.point = a.position + (result.normal * a.radius);
  return result;
}

Contact contact(Circle c, Rect r) {
  Contact result{};
  result.hit = intersects(c, r);
  if (!result.hit) {
    return result;
  }

  const std::int64_t closest_x =
      clamp_raw(c.position.x.value, r.min.x.value, r.max.x.value);
  const std::int64_t closest_y =
      clamp_raw(c.position.y.value, r.min.y.value, r.max.y.value);

  const Vec2 closest_point =
      Vec2{Scalar::from_raw(closest_x), Scalar::from_raw(closest_y)};
  const Vec2 direction = closest_point - c.position;
  result.normal = normalized_direction_or_default(direction, Vec2{1, 0});

  const Scalar distance = distance_between(c.position, closest_point);
  result.penetration = c.radius - distance;
  result.point = closest_point;
  return result;
}

Contact contact(Rect a, Rect b) {
  Contact result{};
  result.hit = intersects(a, b);
  if (!result.hit) {
    return result;
  }

  const Scalar overlap_x = overlap_amount(a.min.x, a.max.x, b.min.x, b.max.x);
  const Scalar overlap_y = overlap_amount(a.min.y, a.max.y, b.min.y, b.max.y);

  const std::int64_t a_center_x_sum = a.min.x.value + a.max.x.value;
  const std::int64_t b_center_x_sum = b.min.x.value + b.max.x.value;
  const std::int64_t a_center_y_sum = a.min.y.value + a.max.y.value;
  const std::int64_t b_center_y_sum = b.min.y.value + b.max.y.value;

  if (overlap_x.value <= overlap_y.value) {
    result.normal = Vec2{(b_center_x_sum >= a_center_x_sum) ? 1 : -1, 0};
    result.penetration = overlap_x;
  } else {
    result.normal = Vec2{0, (b_center_y_sum >= a_center_y_sum) ? 1 : -1};
    result.penetration = overlap_y;
  }

  const Scalar point_x = scalar_max(a.min.x, b.min.x) +
                         (overlap_x * Scalar::from_raw(kScalarScale / 2));
  const Scalar point_y = scalar_max(a.min.y, b.min.y) +
                         (overlap_y * Scalar::from_raw(kScalarScale / 2));
  result.point = Vec2{point_x, point_y};
  return result;
}

}  // namespace sim
