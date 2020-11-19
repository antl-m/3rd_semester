#ifndef SFMLGAME_SRC_MAINSCENEWINDOW_MAINSCENEWINDOW_H_
#define SFMLGAME_SRC_MAINSCENEWINDOW_MAINSCENEWINDOW_H_

#include "SFML/Graphics.hpp"

class MainSceneWindow {
 public:
  MainSceneWindow();
 private:
  sf::RenderWindow main_window_;
  Player player_;
  Player opponent_;
  std::array<sf::RectangleShape, 20> background_lines;
};

#endif //SFMLGAME_SRC_MAINSCENEWINDOW_MAINSCENEWINDOW_H_
