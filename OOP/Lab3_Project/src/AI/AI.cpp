#include "AI.h"

#include "SFML/Graphics.hpp"

std::size_t Vertex(std::size_t x, std::size_t y) {
  return 9 * y + x;
}

bool AI::CheckWallValid(const Wall &wall) {

  return true;
}

bool AI::CheckTurnValid(int x, int y) {
  return true;
}

AI::AI() :
    board_(9 * 9)
    {
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
}
