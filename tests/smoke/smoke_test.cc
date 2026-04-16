#include <cassert>

#include "sim/scalar.h"
#include "sim/vec2.h"
#include "sim/world.h"

int main() {
  sim::World world;
  world.tick();
  assert(world.tick_count() == 1);

  const sim::Scalar scalar_sum = sim::Scalar{1} + sim::Scalar{2};
  assert(scalar_sum.to_double() == 3.0);

  const sim::Scalar scalar_product = sim::Scalar{2} * sim::Scalar{3};
  assert(scalar_product.to_double() == 6.0);

  const sim::Scalar fractional_product = sim::Scalar{0.5} * sim::Scalar{2};
  assert(fractional_product.to_double() == 1.0);

  const sim::Vec2 vec_sum = sim::Vec2{1, 2} + sim::Vec2{3, 4};
  assert(vec_sum.x.to_double() == 4.0);
  assert(vec_sum.y.to_double() == 6.0);

  const sim::Vec2 vec_product = sim::Vec2{1, 2} * sim::Scalar{3};
  assert(vec_product.x.to_double() == 3.0);
  assert(vec_product.y.to_double() == 6.0);

  return 0;
}
