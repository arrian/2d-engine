#include "World.h"

#include <iostream>

#include <allegro5/allegro_primitives.h>

#include "CellLoader.h"
#include "Settings.h"


World::World(std::string worldPath, std::string dataPath)
  : data(dataPath),
    dataPath(dataPath),
    worldPath(worldPath),
    player(WorldPosition(DEFAULT_PLAYER_START))//CELL_SIZE / 2, CELL_SIZE / 2, 0, 0))
{ 
}

World::~World(void)
{
}

void World::draw(Display* display)
{
  for(std::vector<std::shared_ptr<Cell> >::iterator it = cells.begin(); it != cells.end(); ++it)
  {
    (*it)->draw(display);
  }

  player.draw(display);

}

void World::update(double elapsedSeconds)
{
  for(std::vector<std::shared_ptr<Cell> >::iterator it = cells.begin(); it != cells.end(); ++it)
  {
    (*it)->update(elapsedSeconds);
  }

  player.update();
}

Cell* World::loadCell(int x, int y)
{
  std::shared_ptr<Cell> cell(CellLoader::load(x, y, worldPath, data));
  cells.push_back(cell);

  //add player
  if(x == player.getPosition().xCell && y == player.getPosition().yCell)
  {
    cell->addPlayer(&player);
  }

  return cell.get();
}

void World::unloadCell(int x, int y)
{
  throw std::runtime_error("unload cell not implemented");
}

