#include <SFML/Graphics.hpp>

class Cell {
public:
  Cell() {};
  void create(float size, float x, float y);
  sf::RectangleShape getShape() { return rectangleShape; }
  
  bool getIsAlive() { return isAlive; }
  void setIsAlive(bool value);

  int aliveNeighbours;

private:
  sf::RectangleShape rectangleShape;
  sf::Color aliveColor = sf::Color::White;
  sf::Color deadColor = sf::Color(7, 7, 7);
  sf::Color outlineColor = sf::Color(0, 0, 0);

  bool isAlive = false;
  float x, y;

  void updateColorState();
};
