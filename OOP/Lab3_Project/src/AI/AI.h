#ifndef SFMLGAME_SRC_AI_AI_H_
#define SFMLGAME_SRC_AI_AI_H_

#include "../Wall/Wall.h"

class AI {
 public:
  AI();
  bool TryPutWall(const Wall &wall);
  bool TryMakeTurn(int x, int y);
 private:
  Board board_;
  Walls available_walls_;
  std::size_t player_walls_reserve_;
  std::size_t opponent_walls_reserve_;
  std::size_t player_v_;
  std::size_t opponent_v_;
};

#endif //SFMLGAME_SRC_AI_AI_H_
