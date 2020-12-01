#ifndef SFMLGAME_SRC_MAINSCENEWINDOW_MAINSCENEWINDOW_H_
#define SFMLGAME_SRC_MAINSCENEWINDOW_MAINSCENEWINDOW_H_

#include "../Player/Player.h"
#include "../Wall/Wall.h"
#include "../AI/AI.h"

#include "SFML/Graphics.hpp"

class MainSceneWindow {
 public:
  MainSceneWindow();
  void Launch();

 private:
  void DisplayAll();
  bool LeftMouseAction(sf::Vector2i pos);
  bool RightMouseAction(sf::Vector2i pos);
  void MakeOpponentTurn();
  void Restart();
 private:
  sf::ContextSettings settings_;
  sf::RenderWindow main_window_;
  Player player_;
  Player opponent_;
  std::vector<sf::RectangleShape> tiles_;
  Walls walls_;
  AI ai_;
};

#endif //SFMLGAME_SRC_MAINSCENEWINDOW_MAINSCENEWINDOW_H_
