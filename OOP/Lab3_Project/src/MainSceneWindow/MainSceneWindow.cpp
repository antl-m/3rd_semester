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
  font_.loadFromFile("../../rsc/Fonts/Quicksand-Bold.ttf");
  game_over_text_.setFont(font_);
  game_over_text_.setOutlineColor(sf::Color::Black);
  game_over_text_.setOutlineThickness(10);
  game_over_text_.setCharacterSize(380);
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
        if (ai_.WasGameOver()) {
          Restart();
        } else {
          bool was_player_turn = false;
          if (event.key.code == sf::Mouse::Left) {
            was_player_turn = LeftMouseAction(pos);
          }
          if (was_player_turn) {
            MakeOpponentTurn();
          }
        }
      }
    }
    if (!ai_.WasGameOver())
      Preview(pos);
    else
      GameOver();
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
  if (player_preview_) {
    main_window_.draw(*player_preview_);
    player_preview_.reset();
  }
  if (wall_preview_) {
    main_window_.draw(*wall_preview_);
    wall_preview_.reset();
  }
  main_window_.draw(game_over_text_);
  game_over_text_.setString("");
  main_window_.display();
}

bool MainSceneWindow::LeftMouseAction(sf::Vector2i pos) {
  int x = pos.x / 88;
  int y = pos.y / 88;
  bool was_turn = false;
  if (pos.x % 88 > 8 && pos.y % 88 > 8) {
    was_turn = ai_.TryMakeTurn(x, y);
    if (was_turn)
      player_.SetPosition(x, y);
  }
  if (was_turn)
    return was_turn;

  x = pos.x / 88;
  y = pos.y / 88;
  if (x < 9 && y < 9) {
    if (y > 0 && x < 8 && (pos.x % 88) > 8 && (pos.y % 88) <= 8) {
      Wall wall(x, y, Wall::Type::Horizontal);
      was_turn = ai_.TryPutWall(wall);
      if (was_turn) {
        walls_.insert(wall);
      }
    } else if (y < 8 && x > 0 && (pos.x % 88) <= 8 && (pos.y % 88) > 8) {
      Wall wall(x, y, Wall::Type::Vertical);
      was_turn = ai_.TryPutWall(wall);
      if (was_turn) {
        walls_.insert(wall);
      }
    }
  }
  return was_turn;
}

void MainSceneWindow::MakeOpponentTurn() {
  auto turn = ai_.OpponentTurn();
  if (turn.index() == 0) {
    auto[x, y] = *std::get_if<sf::Vector2i>(&turn);
    opponent_.SetPosition(x, y);
  } else {
    Wall w = *std::get_if<Wall>(&turn);
    walls_.insert(w);
  }
}

void MainSceneWindow::Restart() {
  player_.SetPosition(4, 8);
  opponent_.SetPosition(4, 0);
  walls_.clear();
  ai_ = AI();
}

void MainSceneWindow::Preview(sf::Vector2i pos) {
  int x = pos.x / 88;
  int y = pos.y / 88;
  bool was_wall_preview = false;
  if (x < 9 && y < 9) {
    if (y > 0 && x < 8 && (pos.x % 88) > 8 && (pos.y % 88) <= 8) {
      Wall wall(x, y, Wall::Type::Horizontal);
      wall.setFillColor(MyColors::kWallPreviewColor);
      wall.setOutlineColor(sf::Color(0, 0, 0, 100));
      if (ai_.CheckWall(wall))
        wall_preview_ = std::move(wall);
      was_wall_preview = true;
    } else if (y < 8 && x > 0 && (pos.x % 88) <= 8 && (pos.y % 88) > 8) {
      Wall wall(x, y, Wall::Type::Vertical);
      wall.setFillColor(MyColors::kWallPreviewColor);
      wall.setOutlineColor(sf::Color(0, 0, 0, 100));
      if (ai_.CheckWall(wall))
        wall_preview_ = std::move(wall);
      was_wall_preview = true;
    }
  }
  if (!was_wall_preview) {
    x = pos.x / 88;
    y = pos.y / 88;
    if (pos.x % 88 > 8 && pos.y % 88 > 8) {
      if (ai_.CheckTurn(x, y)) {
        player_preview_ = Player(MyColors::kPlayerPreviewColor);
        player_preview_->SetPosition(x, y);
      }
    }
  }
}

void MainSceneWindow::GameOver() {
  if (ai_.PlayerWin()) {
    game_over_text_.setString("WIN");
    game_over_text_.setFillColor(MyColors::kPlayerColor);
  } else {
    game_over_text_.setString("FAIL");
    game_over_text_.setFillColor(MyColors::kOpponentColor);
  }
  game_over_text_.setOrigin(game_over_text_.getLocalBounds().width / 2,
                            game_over_text_.getLocalBounds().height / 1.2);
  game_over_text_.setPosition(400, 400);
}
