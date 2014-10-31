#pragma once

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"

#include <Box2D/Box2D.h>

#include "Shape.h"
#include "Position.h"
#include "DataType.h"
#include "Id.h"

class ShapeLine : public Shape
{
public:
  Position v;

  ShapeLine(Position v)
    : v(v)
  {
  }

  virtual void draw(ScreenPosition position, double rotation, double scale)
  {
    al_draw_line((float) (position.x), (float) (position.y), (float) (position.x + (v.x * scale)), (float) (position.y + (-v.y * scale)), al_map_rgb(0,255,0), DEFAULT_LINE_WIDTH * scale);
  }

  virtual void createStaticPhysics(WorldPosition start, b2Body* body, float density, float restitution, Id* id)
  {
    b2Vec2 v1(start.x, start.y);
    b2Vec2 v2(start.x + v.x, start.y + v.y);
    
    b2EdgeShape edge;
    edge.Set(v1, v2);

    b2FixtureDef fixture;
    fixture.density = density;
    fixture.restitution = restitution;
    fixture.shape = &edge;
    fixture.userData = id;

    body->CreateFixture(&fixture);
  }
};




