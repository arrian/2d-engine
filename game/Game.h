#pragma once

#include <iostream>
#include <map>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_ttf.h"

#include "World.h"
#include "Menu.h"
#include "Display.h"
#include "FontUtil.h"
#include "FactoryException.h"

class Game
{
public:
  Game(bool fullscreen);
  ~Game(void);

  void run();

private:
  Display* _display;
  ALLEGRO_DISPLAY* display;
  ALLEGRO_EVENT_QUEUE* event_queue;
  ALLEGRO_TIMER* timer;

  ALLEGRO_FONT* debugFont;

  World world;
  Menu menu;

  Cell* cell;

  bool redraw;

  void draw();
  void update(double elapsedSeconds);

  bool minusPressed;
};



