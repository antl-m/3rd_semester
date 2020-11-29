#include "MainSceneWindow.h"
#include "../Colors/Colors.h"
#include "../Utility/Utility.h"

MainSceneWindow::MainSceneWindow() :
    settings_(0, 0, 8),
    main_window_(sf::VideoMode(800, 800), "Coridors", sf::Style::Close, settings_),
    player_(MyColors::kPlayerColor),
    opponent_(MyColors::kOpponentColor),
    tiles_(9 * 9, sf::RectangleShape(sf::Vector2f(80, 80))) {

  main_window_.setFramerateLimit(60);
  player_.SetPosition(4, 8);
  opponent_.SetPosition(4, 0);
  int i = 0;
  for (auto &tile: tiles_) {
    tile.setOutlineThickness(8);
    tile.setFillColor(MyColors::kTileFillColor);
    tile.setOutlineColor(MyColors::kTileOutlineColor);
    tile.move(CoordToWindow(i % 9, i / 9));
    ++i;
  }
}

void MainSceneWindow::Launch() {
  while (main_window_.isOpen()) {
    sf::Vector2i pos = sf::Mouse::getPosition(main_window_);
    sf::Event event;
    while (main_window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        main_window_.close();
      }
      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.key.code == sf::Mouse::Left) {
          LeftMouseAction(pos);
        } else if (event.key.code == sf::Mouse::Right) {
          RightMouseAction(pos);
        }
      }
    }
    DisplayAll();
  }
}

void MainSceneWindow::DisplayAll() {
  for (auto &tile: tiles_) {
    main_window_.draw(tile);
  }
  for (auto &wall: walls_) {
    main_window_.draw(wall);
  }
  main_window_.draw(opponent_);
  main_window_.draw(player_);
  main_window_.display();
}

void MainSceneWindow::LeftMouseAction(sf::Vector2i pos) {
  int x = pos.x / 88;
  int y = pos.y / 88;
  if (pos.x % 88 > 8 && pos.y % 88 > 8) {
    if(ai_.TryMakeTurn(x, y))
      player_.SetPosition(x, y);
  }
}

void MainSceneWindow::RightMouseAction(sf::Vector2i pos) {
  int x = pos.x / 88;
  int y = pos.y / 88;
  if (x < 9 && y < 9) {
    if (y > 0 && x < 8 && (pos.x % 88) > 8 && (pos.y % 88) <= 8) {
      Wall wall(x, y, Wall::Type::Horizontal);
      std::cerr<<x << ' ' << y << std::endl;
      if (ai_.TryPutWall(wall)) {
        walls_.insert(wall);
      }
    } else if (y < 8 && x > 0 && (pos.x % 88) <= 8 && (pos.y % 88) > 8) {
      Wall wall(x, y, Wall::Type::Vertical);
      std::cerr<<x << ' ' << y << std::endl;
      if (ai_.TryPutWall(wall)) {
        walls_.insert(wall);
      }
    }
  }
}
