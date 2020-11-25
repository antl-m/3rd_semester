#include "AI.h"

#include "SFML/Graphics.hpp"

std::size_t Vertex(std::size_t x, std::size_t y) {
  return 9 * y + x;
}

bool AI::TryPutWall(const Wall &wall) {

  return true;
}

bool AI::TryMakeTurn(int x, int y) {
  return true;
}

AI::AI() :
    board_(9 * 9) {
  //Filling edges
  for (std::size_t x = 0; x < 9; ++x) {
    for (std::size_t y = 0; y < 8; ++y) {
      boost::add_edge(Vertex(x, y), Vertex(x, y + 1), board_);
      if (x < 8) {
        boost::add_edge(Vertex(x, y), Vertex(x + 1, y), board_);
        if (y == 7) {
          boost::add_edge(Vertex(x, y + 1), Vertex(x + 1, y + 1), board_);
        }
      }
    }
  }
  //Filling available walls
  for (std::size_t x = 1; x <= 8; ++x) {
    for (std::size_t y = 0; y <= 7; ++y) {
      available_walls_.emplace(x, y, Wall::Type::Vertical);
    }
  }
  for (std::size_t x = 0; x <= 7; ++x) {
    for (std::size_t y = 1; y <= 8; ++y) {
      available_walls_.emplace(x, y, Wall::Type::Horizontal);
    }
  }
}
