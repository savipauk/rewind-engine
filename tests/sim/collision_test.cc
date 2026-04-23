#include <cassert>

#include "sim/collision.h"

namespace {

void assert_vec2_raw(const sim::Vec2& value, int x, int y) {
  assert(value.x.value == x * sim::kScalarScale);
  assert(value.y.value == y * sim::kScalarScale);
}

void assert_scalar_raw(const sim::Scalar& value, int integer_value) {
  assert(value.value == integer_value * sim::kScalarScale);
}

void test_circle_circle_intersects() {
  const sim::Circle a{sim::Vec2{0, 0}, sim::Scalar{2}};

  const sim::Circle separate{sim::Vec2{5, 0}, sim::Scalar{2}};
  assert(!sim::intersects(a, separate));

  const sim::Circle touch{sim::Vec2{4, 0}, sim::Scalar{2}};
  assert(sim::intersects(a, touch));

  const sim::Circle overlap{sim::Vec2{3, 0}, sim::Scalar{2}};
  assert(sim::intersects(a, overlap));
}

void test_circle_circle_contact() {
  const sim::Circle a{sim::Vec2{0, 0}, sim::Scalar{2}};

  const sim::Contact overlap = sim::contact(a, sim::Circle{sim::Vec2{3, 0}, sim::Scalar{2}});
  assert(overlap.hit);
  assert_vec2_raw(overlap.normal, 1, 0);
  assert_scalar_raw(overlap.penetration, 1);

  const sim::Contact touch = sim::contact(a, sim::Circle{sim::Vec2{4, 0}, sim::Scalar{2}});
  assert(touch.hit);
  assert_vec2_raw(touch.normal, 1, 0);
  assert(touch.penetration.value == 0);

  const sim::Contact separate = sim::contact(a, sim::Circle{sim::Vec2{5, 0}, sim::Scalar{2}});
  assert(!separate.hit);
}

void test_circle_rect_intersects() {
  const sim::Rect r{sim::Vec2{0, 0}, sim::Vec2{10, 10}};

  assert(!sim::intersects(sim::Circle{sim::Vec2{-2, 5}, sim::Scalar{1}}, r));
  assert(sim::intersects(sim::Circle{sim::Vec2{-1, 5}, sim::Scalar{1}}, r));
  assert(sim::intersects(sim::Circle{sim::Vec2{-1, 5}, sim::Scalar{2}}, r));
}

void test_circle_rect_contact() {
  const sim::Rect r{sim::Vec2{0, 0}, sim::Vec2{10, 10}};

  const sim::Contact overlap = sim::contact(sim::Circle{sim::Vec2{-1, 5}, sim::Scalar{2}}, r);
  assert(overlap.hit);
  assert_vec2_raw(overlap.normal, 1, 0);
  assert_scalar_raw(overlap.penetration, 1);

  const sim::Contact touch = sim::contact(sim::Circle{sim::Vec2{-1, 5}, sim::Scalar{1}}, r);
  assert(touch.hit);
  assert_vec2_raw(touch.normal, 1, 0);
  assert(touch.penetration.value == 0);

  const sim::Contact separate = sim::contact(sim::Circle{sim::Vec2{-2, 5}, sim::Scalar{1}}, r);
  assert(!separate.hit);
}

void test_rect_rect_intersects() {
  const sim::Rect a{sim::Vec2{0, 0}, sim::Vec2{10, 10}};

  assert(!sim::intersects(a, sim::Rect{sim::Vec2{11, 2}, sim::Vec2{14, 8}}));
  assert(sim::intersects(a, sim::Rect{sim::Vec2{10, 2}, sim::Vec2{14, 8}}));
  assert(sim::intersects(a, sim::Rect{sim::Vec2{8, 2}, sim::Vec2{14, 8}}));
}

void test_rect_rect_contact() {
  const sim::Rect a{sim::Vec2{0, 0}, sim::Vec2{10, 10}};

  const sim::Contact overlap = sim::contact(a, sim::Rect{sim::Vec2{8, 2}, sim::Vec2{14, 8}});
  assert(overlap.hit);
  assert_vec2_raw(overlap.normal, 1, 0);
  assert_scalar_raw(overlap.penetration, 2);

  const sim::Contact touch = sim::contact(a, sim::Rect{sim::Vec2{10, 2}, sim::Vec2{14, 8}});
  assert(touch.hit);
  assert_vec2_raw(touch.normal, 1, 0);
  assert(touch.penetration.value == 0);

  const sim::Contact separate = sim::contact(a, sim::Rect{sim::Vec2{11, 2}, sim::Vec2{14, 8}});
  assert(!separate.hit);
}

}  // namespace

int main() {
  test_circle_circle_intersects();
  test_circle_circle_contact();
  test_circle_rect_intersects();
  test_circle_rect_contact();
  test_rect_rect_intersects();
  test_rect_rect_contact();
  return 0;
}
