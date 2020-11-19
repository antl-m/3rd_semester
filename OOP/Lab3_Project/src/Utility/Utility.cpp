#include "Utility.h"

#include <cassert>

sf::Vector2f CoordToWindow(int x, int y) {
  assert(x >= 0 && x < 9);
  assert(y >= 0 && y < 9);
  float x_f = 8 + 88 * x;
  float y_f = 8 + 88 * y;
  return sf::Vector2f(x_f, y_f);
}
