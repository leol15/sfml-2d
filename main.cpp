#include <SFML/Graphics.hpp>
// #include <Color.hpp>
#include "World2D.h"

int main()
{
  sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
  sf::CircleShape shape(400.f);
  shape.setFillColor(sf::Color::Green);

  World2D world(800, 800);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    world.update();

    window.clear();
    // window.draw(shape);
    world.render(window);
    window.display();

    // update
    shape.setFillColor(sf::Color(10, 10, 40));
  }

  return 0;
}