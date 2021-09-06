#include "include/cell.hpp"

void Cell::create(float cellSize, float posX, float posY) 
{
  x = posX;
  y = posY;

  rectangleShape = sf::RectangleShape(sf::Vector2f(cellSize, cellSize));
  rectangleShape.setPosition(posX, posY);
  updateColorState();

  // Adding the outline
  rectangleShape.setOutlineThickness(2);
  rectangleShape.setOutlineColor(outlineColor);
}

void Cell::updateColorState() 
{
  // Determining the cell's color based on its state
  rectangleShape.setFillColor(isAlive ? aliveColor : deadColor);
}

void Cell::setIsAlive(bool value) 
{
  isAlive = value;

  updateColorState();
}
