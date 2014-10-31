#pragma once

#include <vector>

#include "Data.h"
#include "Cell.h"
#include "Player.h"
#include "Creature.h"
#include "Environment.h"
#include "Display.h"

class World
{
public:
  World(std::string worldPath, std::string dataPath);
  ~World(void);

  void update(double elapsedSeconds);
  void draw(Display* display);

  Cell* loadCell(int x, int y);
  void unloadCell(int x, int y);

  Player* getPlayer() {return &player;}

private:
  std::string dataPath;
  std::string worldPath;

  Data data;
  Environment environment;

  Player player;
  std::vector<std::shared_ptr<Cell> > cells;
  std::vector<std::shared_ptr<Creature> > creatures;
};

