#pragma once

#include "Util.h"

#include "WorldManager.h"
#include "ScriptManager.h"
#include "SettingsManager.h"

class GameCore : public enable_shared_from_this<GameCore>
{
public:
  GameCore(shared_ptr<Core> core);
  ~GameCore(void);

  void update();

  shared_ptr<GameCore> getThis();

  shared_ptr<Core> getCore();
  void setCore(shared_ptr<Core> core);

  shared_ptr<WorldManager> getWorldManager();
  shared_ptr<ScriptManager> getScriptManager();
  shared_ptr<SettingsManager> getSettingsManager();

  static shared_ptr<GameCore> getGlobal();//allow embedded scripts to get the exposed game core
  static void setGlobal(shared_ptr<GameCore> gameCore);//expose a specific game core to embedded scripts

private:
  shared_ptr<Core> core;

  shared_ptr<WorldManager> worldManager;
  shared_ptr<ScriptManager> scriptManager;
  shared_ptr<SettingsManager> settingsManager;

};

extern shared_ptr<GameCore> GAME_CORE_GLOBAL;
