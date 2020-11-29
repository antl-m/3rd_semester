#include "AI.h"

#include "SFML/Graphics.hpp"

#include <iostream>

std::size_t Vertex(std::size_t x, std::size_t y) {
  return 9 * y + x;
}

sf::Vector2i VertexToCoord(int vrt) {
  return {vrt % 9, vrt / 9};
}

void AI::PutWallToBoard(const Wall &wall) {
  auto[w_x, w_y] = wall.GetCoord();
  if (wall.GetType() == Wall::Type::Vertical) {
    board_.pop_edge(Vertex(w_x, w_y), Vertex(w_x - 1, w_y));
    board_.pop_edge(Vertex(w_x, w_y + 1), Vertex(w_x - 1, w_y + 1));
  } else {
    board_.pop_edge(Vertex(w_x, w_y), Vertex(w_x, w_y - 1));
    board_.pop_edge(Vertex(w_x + 1, w_y), Vertex(w_x + 1, w_y - 1));
  }
}

void AI::TakeWallFromBoard(const Wall &wall) {
  auto[w_x, w_y] = wall.GetCoord();
  if (wall.GetType() == Wall::Type::Vertical) {
    board_.push_edge(0, Vertex(w_x, w_y), Vertex(w_x - 1, w_y));
    board_.push_edge(0, Vertex(w_x, w_y + 1), Vertex(w_x - 1, w_y + 1));
  } else {
    board_.push_edge(0, Vertex(w_x, w_y), Vertex(w_x, w_y - 1));
    board_.push_edge(0, Vertex(w_x + 1, w_y), Vertex(w_x + 1, w_y - 1));
  }
}

bool AI::CheckWall(const Wall &wall) {
  if (available_walls_.contains(wall)) {
    PutWallToBoard(wall);
    auto player_dist_to_v = board_.length(player_v_);
    auto opponent_dist_to_v = board_.length(opponent_v_);
    bool is_player_path = false;
    bool is_opponent_path = false;
    for (std::size_t x = 0; x < 9; ++x) {
      is_player_path = is_player_path || !player_dist_to_v[Vertex(x, 0)].empty();
      std::cout << player_dist_to_v[Vertex(x, 0)] << std::endl;
      is_opponent_path = is_opponent_path || !opponent_dist_to_v[Vertex(x, 8)].empty();
    }
    TakeWallFromBoard(wall);
    return is_player_path && is_opponent_path;
  }
  return false;
}

bool AI::TryPutWall(const Wall &wall) {
  bool result = CheckWall(wall);
  if (result) {
    auto[w_x, w_y] = wall.GetCoord();
    if (wall.GetType() == Wall::Type::Vertical) {
      available_walls_.erase(Wall(w_x - 1, w_y + 1, Wall::Type::Horizontal));
      available_walls_.erase(Wall(w_x, w_y - 1, Wall::Type::Vertical));
      available_walls_.erase(Wall(w_x, w_y, Wall::Type::Vertical));
      available_walls_.erase(Wall(w_x, w_y + 1, Wall::Type::Vertical));
    } else {
      available_walls_.erase(Wall(w_x + 1, w_y - 1, Wall::Type::Vertical));
      available_walls_.erase(Wall(w_x - 1, w_y, Wall::Type::Horizontal));
      available_walls_.erase(Wall(w_x, w_y, Wall::Type::Horizontal));
      available_walls_.erase(Wall(w_x + 1, w_y, Wall::Type::Horizontal));
    }
    PutWallToBoard(wall);
  }
  return result;
}
bool AI::TryMakeTurn(int x, int y) {
  player_v_ = Vertex(x, y);
  return true;
}
AI::AI() :
    player_walls_reserve_(10),
    opponent_walls_reserve_(10),
    player_v_(Vertex(4, 8)),
    opponent_v_(Vertex(4, 0)) {
  //Filling vertexes
  for (std::size_t kI = 0; kI < 81; ++kI) {
    board_.push_vertex(kI);
  }
  //Filling edges
  for (std::size_t x = 0; x < 9; ++x) {
    for (std::size_t y = 0; y < 8; ++y) {
      board_.push_edge(0, Vertex(x, y), Vertex(x, y + 1));
      if (x < 8) {
        board_.push_edge(0, Vertex(x, y), Vertex(x + 1, y));
        if (y == 7) {
          board_.push_edge(0, Vertex(x, y + 1), Vertex(x + 1, y + 1));
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
