#include <SFML/Graphics.hpp>
// #include <Color.hpp>
#include "World2D.h"

constexpr int W = 800;
constexpr int H = 800;

int main()
{
  sf::RenderWindow window(sf::VideoMode(W, H), "SFML works!");
  window.setFramerateLimit(60);

  sf::CircleShape shape(400.f);
  shape.setFillColor(sf::Color::Green);

  World2D world(W, H);

  while (window.isOpen())
  {
    world.handleEvents(window);

    window.clear();
    world.render(window);
    window.display();

    // update
    // shape.setFillColor(sf::Color(10, 10, 40));
  }

  return 0;
}