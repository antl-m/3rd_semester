#include "Wall.h"
#include "../Colors/Colors.h"

#include <cassert>

Wall::Wall(int x, int y, Type type) :
    type_(type),
    x_(x), y_(y) {
  setFillColor(MyColors::kWallColor);
  Move(x_, y_);
  Resize();
}

void Wall::Move(int x, int y) {
  x_ = x;
  y_ = y;
  move(Wall::CoordToWindow(x_, y_));
}

void Wall::SetType(Type type) {
  type_ = type;
  Resize();
}

void Wall::Resize() {
  switch (type_) {
    case Type::Horizontal: setSize(sf::Vector2f(184, 8));
      break;
    case Type::Vertical: setSize(sf::Vector2f(8, 184));
      break;
    default: throw std::runtime_error("Resize: Invalid Wall::Type");
  }
}

sf::Vector2f Wall::CoordToWindow(int x, int y) {
  //TODO:DELETE
  assert(x >= 0 && x < 9);
  assert(y >= 0 && y < 9);
  float x_f = x * 88;
  float y_f = y * 88;
  return sf::Vector2f(x_f, y_f);
}

bool operator==(const Wall &lhs, const Wall &rhs) {
  return lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_ && lhs.type_ == rhs.type_;
}

std::size_t Wall::Hasher::operator()(const Wall &wall) const {
  auto t = static_cast<std::size_t>(wall.type_);
  static constexpr std::size_t seed = 524827;
  return seed * seed * wall.x_ + seed * wall.y_ + t;
}
