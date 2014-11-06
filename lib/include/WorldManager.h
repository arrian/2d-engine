#pragma once

#include <memory>
using namespace std;

#include <Polycode.h>
#include "Polycode2DPhysics.h"
using namespace Polycode;

class WorldManager
{
public:
  WorldManager();
  ~WorldManager(void);

  void update();

private:
	shared_ptr<PhysicsScene2D> scene;

};

