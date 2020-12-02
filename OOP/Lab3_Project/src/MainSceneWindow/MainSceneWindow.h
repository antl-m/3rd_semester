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
  void MakeOpponentTurn();
  void Restart();
  void Preview(sf::Vector2i pos);
  void GameOver();
 private:
  sf::ContextSettings settings_;
  sf::RenderWindow main_window_;
  Player player_;
  Player opponent_;
  std::vector<sf::RectangleShape> tiles_;
  Walls walls_;
  AI ai_;
  std::optional<Player> player_preview_;
  std::optional<Wall> wall_preview_;
  sf::Text game_over_text_;
  sf::Font font_;
};

#endif //SFMLGAME_SRC_MAINSCENEWINDOW_MAINSCENEWINDOW_H_
