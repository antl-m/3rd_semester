#ifndef SFMLGAME_SRC_AI_AI_H_
#define SFMLGAME_SRC_AI_AI_H_

#include <variant>
#include "../Wall/Wall.h"
#include "../Graph/Graph.h"

using Board = LinkedGraph<int, int>;

class AI {
 public:
  AI();
  bool TryPutWall(const Wall &wall);
  bool TryMakeTurn(int x, int y);
  std::variant<sf::Vector2i, Wall> OpponentTurn();
  bool WasGameOver();
  bool CheckTurn(int x, int y);
  bool PlayerWin();
  bool CheckWall(const Wall &wall);
 private:
  void PutWallToBoard(const Wall &wall);
  void TakeWallFromBoard(const Wall &wall);
  std::pair<int, std::vector<int>> BestBenefitAndWay();
  std::vector<std::vector<int>> PlayerMinPaths();
  std::vector<std::vector<int>> OpponentMinPaths();
  void PutOpponentWall(const Wall& w);
 private:
  Board board_;
  Walls available_walls_;
  std::size_t player_walls_reserve_;
  std::size_t opponent_walls_reserve_;
  std::size_t player_v_;
  std::size_t opponent_v_;
  bool was_game_over_;
  bool player_win_;
};

#endif //SFMLGAME_SRC_AI_AI_H_
