#pragma once

#include <vector>
#include <iostream>
#include <map>
#include <string>

#include <Polycode.h>
using namespace Polycode;

#include "WorldManager.h"
#include "ScriptManager.h"
#include "SettingsManager.h"

class GameCore
{
public:
  GameCore(Core* core);
  ~GameCore(void);

  void update();

  Core* getCore();
  void setCore(Core* core);

  WorldManager* getWorldManager();
  ScriptManager* getScriptManager();
  SettingsManager* getSettingsManager();

private:
  Core* core;

  WorldManager worldManager;
  ScriptManager scriptManager;
  SettingsManager settingsManager;

};