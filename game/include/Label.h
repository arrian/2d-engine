#pragma once

#include <string>

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_primitives.h"

#include "Position.h"

class Label
{
  std::string text;
  ALLEGRO_FONT* font;
  ALLEGRO_COLOR textColour;
  ALLEGRO_COLOR outlineColour;

  float radius;
  float distance;
  float thickness;

  Label(std::string text)
    : text(text)
  {
  }

  void draw(ScreenPosition target)
  {
    al_draw_circle(target.x, target.y, radius, outlineColour, thickness);
    al_draw_line(target.x, target.y - radius, target.x, (target - radius) - distance, outlineColour, thickness);
    //TODO: draw text
    al_draw_text(font, textColour, position.x, position.y, 0, text.c_str());
  }

};



