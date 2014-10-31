#pragma once

#include "MainMenu.h"
#include "GameMenu.h"
#include "MapMenu.h"

class Menu
{
public:
  Menu(void) {}
  ~Menu(void) {}

private:
  MainMenu mainMenu;
  GameMenu gameMenu;
  MapMenu mapMenu;
};

