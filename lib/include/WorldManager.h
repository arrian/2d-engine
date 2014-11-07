#pragma once

#include "Util.h"

class WorldManager
{
public:
  WorldManager();
  ~WorldManager(void);

  void update();

private:
	shared_ptr<PhysicsScene2D> scene;

};

