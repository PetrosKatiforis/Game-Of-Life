#include <SFML/Graphics.hpp>
#include "include/game.hpp"

void Game::run() 
{
  // Setting up the window
  window.create(
    sf::VideoMode(GRID_WIDTH * CELL_SIZE, GRID_HEIGHT * CELL_SIZE),
    "Conway's Game Of Life, C++ Implementation",
    sf::Style::Titlebar | sf::Style::Close
  );

  window.setFramerateLimit(30);

  // Generating the grid, initializing the cells
  generateGrid();

  while (window.isOpen()) 
  {
    while (window.pollEvent(event)) 
    {
      if (event.type == sf::Event::Closed)
        window.close();

      // Handling input events
      handleInput();
    }

    processGameLoop();
  }
}

void Game::processGameLoop() 
{
  window.clear(sf::Color(0, 100, 100));

  // Advance to the next generation once every second
  if (timer.getElapsedTime() >= sf::seconds(generationInterval) && 
      !getIsPaused()) 
  {
    advanceGridGeneration();

    timer.restart();
  }

  drawGrid();
  
  window.display();
}

void Game::handleInput() 
{
  if (event.type == sf::Event::KeyPressed)
  {
    switch (event.key.code)
    {
      // Toggle the isPaused setting
      case sf::Keyboard::Space:
        toggleIsPaused();
        break;
    }
  }
  else if (event.type == sf::Event::MouseButtonPressed)
  {
    if (event.mouseButton.button == sf::Mouse::Left)
    {
      // Divide the mouse position by CELL_SIZE to determine the exact grid position
      sf::Vector2i position = sf::Mouse::getPosition(window) / CELL_SIZE;

      Cell* targetCell = &grid[position.y][position.x];
      targetCell->setIsAlive(!targetCell->getIsAlive());
    }
  }
}

void Game::setLivingNeighbours(int i, int j)
{
  grid[i][j].aliveNeighbours = 0;

  // Getting all the neighbours using an offset
  for (int y = -1; y <= 1; y++) 
  {
    for (int x = -1; x <= 1; x++) 
    {
      if (
        !(x == 0 && y == 0) && 
        i + y >= 0 && i + y < GRID_HEIGHT && 
        j + x >= 0 && j + x < GRID_WIDTH && 
        grid[i + y][j + x].getIsAlive()
      )
        grid[i][j].aliveNeighbours++;
    }
  }
}

void Game::advanceGridGeneration() 
{
  // Counting the living neighbours
  for (int i = 0; i < GRID_HEIGHT; i++) 
  {
    for (int j = 0; j < GRID_WIDTH; j++) 
    {
      setLivingNeighbours(i, j);
    }
  }

  // Updating the grid based on the simulation's rules
  for (int i = 0; i < GRID_HEIGHT; i++) 
  {
    for (int j = 0; j < GRID_WIDTH; j++) 
    {
      int neighbours = grid[i][j].aliveNeighbours;
      
      bool willSurvive = (neighbours == 3 || 
        (grid[i][j].getIsAlive() && neighbours == 2));
      
      grid[i][j].setIsAlive(willSurvive);
    }
  }
}

void Game::generateGrid() 
{
  // Initializing cell sizes

  for (int i = 0; i < GRID_HEIGHT; i++) 
  {
    for (int j = 0; j < GRID_WIDTH; j++) 
    {
      grid[i][j].create(CELL_SIZE, j * CELL_SIZE, i * CELL_SIZE);
    }
  }
}

void Game::drawGrid() 
{
  // Drawing cell positions

  for (int i = 0; i < GRID_HEIGHT; i++) 
  {
    for (int j = 0; j < GRID_WIDTH; j++) 
    {
      window.draw(grid[i][j].getShape()); 
    }
  }
}
