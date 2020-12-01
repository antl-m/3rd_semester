#include "AI.h"

#include "SFML/Graphics.hpp"

#include <iostream>
#include <ranges>

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
  if (available_walls_.contains(wall) && player_walls_reserve_ > 0) {
    PutWallToBoard(wall);
    auto player_dist_to_v = board_.length(player_v_);
    auto opponent_dist_to_v = board_.length(opponent_v_);
    bool is_player_path = false;
    bool is_opponent_path = false;
    for (std::size_t x = 0; x < 9; ++x) {
      is_player_path = is_player_path || !player_dist_to_v[Vertex(x, 0)].empty();
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
    --player_walls_reserve_;
  }
  return result;
}

bool AI::CheckTurn(int x, int y) {
  auto[p_x, p_y] = VertexToCoord(player_v_);
  auto[o_x, o_y] = VertexToCoord(opponent_v_);

  std::unordered_set<int> available_turns;
  for (const auto&[a_x, a_y]: std::vector<sf::Vector2i>{{p_x + 1, p_y},
                                                        {p_x - 1, p_y},
                                                        {p_x, p_y + 1},
                                                        {p_x, p_y - 1}}) {
    if (a_x >= 0 && a_x < 9 && a_y >= 0 && a_y < 9 && board_.is_edge(player_v_, Vertex(a_x, a_y)))
      available_turns.insert(Vertex(a_x, a_y));
  }
  if (available_turns.contains(opponent_v_)) {
    for (const auto&[a_x, a_y]: std::vector<sf::Vector2i>{{o_x + 1, o_y},
                                                          {o_x - 1, o_y},
                                                          {o_x, o_y + 1},
                                                          {o_x, o_y - 1}}) {
      if (a_x >= 0 && a_x < 9 && a_y >= 0 && a_y < 9 && board_.is_edge(opponent_v_, Vertex(a_x, a_y)))
        available_turns.insert(Vertex(a_x, a_y));
    }
  }
  available_turns.erase(player_v_);
  available_turns.erase(opponent_v_);
  return available_turns.contains(Vertex(x, y));
}

bool AI::TryMakeTurn(int x, int y) {
  if (CheckTurn(x, y)) {
    player_v_ = Vertex(x, y);
    if (y == 0) {
      player_win_ = true;
      was_game_over_ = true;
    }
    return true;
  }
  return false;
}

AI::AI() :
    player_walls_reserve_(999),
    opponent_walls_reserve_(999),
    player_v_(Vertex(4, 8)),
    opponent_v_(Vertex(4, 0)),
    was_game_over_(false),
    player_win_(false) {
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

int Benefit(std::vector<int> player_way, std::vector<int> opponent_way) {
  int p_size = player_way.size();
  int o_size = opponent_way.size();
  for (int i = 0, my_min = std::min<int>(player_way.size(), opponent_way.size()) - 1; i < my_min; i++) {
    if (player_way[i + 1] == opponent_way[i + 1]) {
      p_size--;
      break;
    } else if (opponent_way[i + 1] == player_way[i]) {
      o_size--;
      break;
    }
  }
  return p_size - o_size;
}

std::vector<std::vector<int>> AI::PlayerMinPaths() {
  auto v_to_dist = board_.length(player_v_);
  std::vector<std::vector<int>> res;
  int min_len = std::numeric_limits<int>::max();
  for (std::size_t x = 0; x < 9; ++x) {
    const std::vector<int> &cur_path = v_to_dist[Vertex(x, 0)];
    if (cur_path.size() < min_len && !cur_path.empty()) {
      min_len = cur_path.size();
      res.clear();
      res.push_back(cur_path);
    } else if (cur_path.size() == min_len) {
      res.push_back(cur_path);
    }
  }
  return res;
}

std::vector<std::vector<int>> AI::OpponentMinPaths() {
  auto v_to_dist = board_.length(opponent_v_);
  std::vector<std::vector<int>> res;
  for (std::size_t x = 0; x < 9; ++x) {
    const std::vector<int> &cur_path = v_to_dist[Vertex(x, 8)];
    if (!cur_path.empty()) {
      res.push_back(cur_path);
    }
  }
  return res;
}

std::pair<int, std::vector<int>> AI::BestBenefitAndWay() {
  std::vector<int> best_way;
  int max_benefit = std::numeric_limits<int>::lowest();
  for (const auto &wp : PlayerMinPaths()) {
    for (const auto &wo : OpponentMinPaths()) {
      int cur_benefit = Benefit(wp, wo);
      if (cur_benefit > max_benefit) {
        max_benefit = cur_benefit;
        best_way = wo;
      }
    }
  }
  return {max_benefit, best_way};
}

std::variant<sf::Vector2i, Wall> AI::OpponentTurn() {
  auto[max_benefit, best_way] = BestBenefitAndWay();

  if (max_benefit <= 0 && opponent_walls_reserve_ > 0) {
    int best_w_x, best_w_y;
    Wall::Type best_w_t;
    int new_max_benefit = std::numeric_limits<int>::lowest();

    for (std::size_t x = 1; x <= 8; ++x) {
      for (std::size_t y = 0; y <= 7; ++y) {
        Wall cur_w(x, y, Wall::Type::Vertical);
        if (CheckWall(cur_w)) {
          PutWallToBoard(cur_w);
          auto[cur_benefit, _] = BestBenefitAndWay();
          TakeWallFromBoard(cur_w);
          if (cur_benefit > new_max_benefit) {
            new_max_benefit = cur_benefit;
            std::tie(best_w_x, best_w_y) = cur_w.GetCoord();
            best_w_t = cur_w.GetType();
          }
        }
      }
    }
    for (std::size_t x = 0; x <= 7; ++x) {
      for (std::size_t y = 1; y <= 8; ++y) {
        Wall cur_w(x, y, Wall::Type::Horizontal);
        if (CheckWall(cur_w)) {
          PutWallToBoard(cur_w);
          auto[cur_benefit, _] = BestBenefitAndWay();
          TakeWallFromBoard(cur_w);
          if (cur_benefit > new_max_benefit) {
            new_max_benefit = cur_benefit;
            std::tie(best_w_x, best_w_y) = cur_w.GetCoord();
            best_w_t = cur_w.GetType();
          }
        }
      }
    }

    if (new_max_benefit > max_benefit) {
      Wall best_wall(best_w_x, best_w_y, best_w_t);
      PutOpponentWall(best_wall);
      return best_wall;
    }
  }
  opponent_v_ = (best_way[0] == player_v_ ? best_way[1] : best_way[0]);
  sf::Vector2i res_move = VertexToCoord(opponent_v_);
  if (res_move.y == 8) {
    player_win_ = false;
    was_game_over_ = true;
  }
  return res_move;
}

void AI::PutOpponentWall(const Wall &w) {
  auto[w_x, w_y] = w.GetCoord();
  if (w.GetType() == Wall::Type::Vertical) {
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
  PutWallToBoard(w);
  --opponent_walls_reserve_;
}

bool AI::WasGameOver() {
  return was_game_over_;
}
