#pragma once

#include "Shape.h"

class ShapePoint : public Shape
{
public:
  virtual void draw(ScreenPosition position, double rotation, double scale)
  {
    al_draw_filled_circle(position.x, position.y, 10 * scale, al_map_rgb(255,0,0));
  }
};




