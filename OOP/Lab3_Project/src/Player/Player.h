#ifndef SFMLGAME_SRC_PLAYER_PLAYER_H_
#define SFMLGAME_SRC_PLAYER_PLAYER_H_

#include "SFML/Graphics.hpp"

class Player : public sf::CircleShape {
 public:
  explicit Player(sf::Color color);
  void SetPosition(int x, int y);
 private:
};

#endif //SFMLGAME_SRC_PLAYER_PLAYER_H_
