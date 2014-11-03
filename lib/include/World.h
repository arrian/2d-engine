#pragma once

#include <vector>
#include <iostream>
#include <map>
#include <string>

#include <Polycode.h>

class World
{
public:
  World(Polycode::Core* core);
  ~World(void);

  void update();

private:
  Polycode::Core* core;

};

