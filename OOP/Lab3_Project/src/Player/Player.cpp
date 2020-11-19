#include "Player.h"

#include "../Utility/Utility.h"

Player::Player(sf::Color color) : sf::CircleShape(40) {
  this->setFillColor(color);
}

void Player::SetPosition(int x, int y) {
  setPosition(CoordToWindow(x, y));
}
