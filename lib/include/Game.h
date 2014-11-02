#pragma once

#include <iostream>
#include <map>
#include <string>

#include <Polycode.h>
#include "PolycodeView.h"

using namespace Polycode;

// #include "World.h"
// #include "Menu.h"
// #include "Display.h"
// #include "FontUtil.h"
// #include "FactoryException.h"

class Game : public EventHandler
{
public:
  Game();
  ~Game(void);

  bool update();

  void handleEvent(Event *e);

private:
  Core *core;

  // World world;
  // Menu menu;

};



