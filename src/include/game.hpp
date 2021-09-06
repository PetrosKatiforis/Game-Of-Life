#include <SFML/Graphics.hpp>
#include "cell.hpp"

class Game {
public:
  Game() {};
  void run();
  void toggleIsPaused() { isPaused = !isPaused; }
  bool getIsPaused() { return isPaused; }

private:
  static const int GRID_WIDTH = 50;
  static const int GRID_HEIGHT = 50;

  const int CELL_SIZE = 10;
  float generationInterval = 0.2f;

  sf::RenderWindow window;
  sf::Event event;
  sf::Clock timer;

  Cell grid[GRID_HEIGHT][GRID_WIDTH];
  bool isPaused = true;
  
  void handleInput();
  void processGameLoop();
  void generateGrid();
  void drawGrid();
  void advanceGridGeneration();
  void setLivingNeighbours(int i, int j);
};
