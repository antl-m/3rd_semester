#ifndef SFMLGAME_SRC_AI_AI_H_
#define SFMLGAME_SRC_AI_AI_H_

#include "../Wall/Wall.h"

class AI {
 public:
  bool CheckWallValid(const Wall &wall);
  bool CheckTurnValid(int x, int y);
 private:
};

#endif //SFMLGAME_SRC_AI_AI_H_
