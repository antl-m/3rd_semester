#ifndef SFMLGAME_SRC_WALL_WALL_H_
#define SFMLGAME_SRC_WALL_WALL_H_

#include "SFML/Graphics.hpp"

#include <unordered_set>

class Wall : public sf::RectangleShape {
 public:
  enum class Type {
    Vertical,
    Horizontal
  };

  struct Hasher {
    std::size_t operator()(const Wall &wall) const;
  };

  friend bool operator==(const Wall &lhs, const Wall &rhs);

 public:
  Wall(int x, int y, Type type);
  void Move(int x, int y);
  void SetType(Type type);
  Type GetType() const;
  std::pair<int, int> GetCoord() const;

 private:
  void Resize();
  static sf::Vector2f CoordToWindow(int x, int y);

 private:
  Type type_;
  std::size_t x_, y_;
};

using Walls = std::unordered_set<Wall, Wall::Hasher>;

#endif //SFMLGAME_SRC_WALL_WALL_H_
