#pragma once

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

#include <Box2D/Box2D.h>

#include "Position.h"
#include "Id.h"

class Shape
{
public:
  virtual void draw(ScreenPosition position, double rotation, double scale) {}

  virtual void createStaticPhysics(WorldPosition start, b2Body* body, float density, float restitution, Id* id) {}
  virtual void createDynamicPhysics(b2Body* body, float density, float friction, Id* id) {}
};




