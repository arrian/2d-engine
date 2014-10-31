#pragma once

#include <math.h>

#include "allegro5/allegro_primitives.h"

#include <Box2D/Box2D.h>

#include "Shape.h"
#include "Id.h"

class ShapeRectangle : public Shape
{
public:
  ShapeRectangle(double width, double height)
    : width(width),
      height(height),
      halfWidth(width / 2),
      halfHeight(height / 2)
  {
  }

  virtual void draw(ScreenPosition position, double rotation, double scale)
  {
    ALLEGRO_VERTEX v[4];

    float sinR = sin(-rotation);
    float cosR = cos(-rotation);
    float sHalfWidth = halfWidth * scale;
    float sHalfHeight = halfHeight * scale;
    
    v[0].x = position.x + sHalfWidth  * cosR - sHalfHeight * sinR;
    v[0].y = position.y + sHalfHeight * cosR + sHalfWidth  * sinR;
    v[1].x = position.x - sHalfWidth  * cosR - sHalfHeight * sinR;
    v[1].y = position.y + sHalfHeight * cosR - sHalfWidth  * sinR;
    v[2].x = position.x - sHalfWidth  * cosR + sHalfHeight * sinR;
    v[2].y = position.y - sHalfHeight * cosR - sHalfWidth  * sinR;
    v[3].x = position.x + sHalfWidth  * cosR + sHalfHeight * sinR;
    v[3].y = position.y - sHalfHeight * cosR + sHalfWidth  * sinR;
    
    al_draw_line(v[0].x,v[0].y,v[1].x,v[1].y,al_map_rgb(0,255,255),DEFAULT_LINE_WIDTH * scale);
    al_draw_line(v[1].x,v[1].y,v[2].x,v[2].y,al_map_rgb(0,255,255),DEFAULT_LINE_WIDTH * scale);
    al_draw_line(v[2].x,v[2].y,v[3].x,v[3].y,al_map_rgb(0,255,255),DEFAULT_LINE_WIDTH * scale);
    al_draw_line(v[3].x,v[3].y,v[0].x,v[0].y,al_map_rgb(0,255,255),DEFAULT_LINE_WIDTH * scale);

    //al_draw_rectangle(position.x - (halfWidth * scale), position.y - (halfHeight * scale), position.x + (halfWidth * scale), position.y + (halfHeight * scale), al_map_rgb(0,255,255), DEFAULT_LINE_WIDTH * scale);
  }

  virtual void createDynamicPhysics(b2Body* body, float density, float friction, Id* id)
  {
    b2PolygonShape shape;
    shape.SetAsBox(halfWidth, halfHeight);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.userData = (void*) id;

    b2Fixture* fixture = body->CreateFixture(&fixtureDef);
  }

  double getWidth()
  {
    return width;
  }

  double getHeight()
  {
    return height;
  }

private:
  double width;
  double height;
  double halfWidth;
  double halfHeight;
};




