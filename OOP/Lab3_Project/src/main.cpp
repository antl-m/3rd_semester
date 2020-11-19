#include "SFML/Graphics.hpp"

#include <vector>
#include <cassert>

using namespace sf;

Vector2f FieldPtToWindowPt(int x, int y) {
  assert(x < 9);
  assert(y < 9);
  float x_f = 8 + 88 * x;
  float y_f = 8 + 88 * y;
  return Vector2f(x_f, y_f);
}

int main() {
  ContextSettings settings;
  settings.antialiasingLevel = 8;

  RenderWindow window(VideoMode(800, 800), "Coridors", Style::Close, settings);
  window.setFramerateLimit(60);

  CircleShape player(40);
  player.move(FieldPtToWindowPt(4, 8));
  player.setFillColor(Color(177, 235, 0));

  std::vector<RectangleShape> tiles(81, RectangleShape(Vector2f(80, 80)));
  int i = 0;
  for (auto &tile: tiles) {
    tile.setOutlineThickness(8);
    tile.setOutlineColor(Color(12, 126, 188));
    tile.setFillColor(Color(83, 187, 244));
    tile.move(8 + (i % 9) * 88, 8 + (i / 9) * 88);
    ++i;
  }

  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed) {
        window.close();
      }

    }
    window.clear(Color::White);
    for (auto &tile: tiles) {
      window.draw(tile);
    }
    window.draw(player);
    window.display();
  }
  return 0;
}