#include "GameCore.h"

shared_ptr<GameCore> GAME_CORE_GLOBAL;

shared_ptr<GameCore> GameCore::getGlobal()
{
	cout << "getting game core" << endl;
	cout << GAME_CORE_GLOBAL << endl;
	return GAME_CORE_GLOBAL;
}

void GameCore::setGlobal(shared_ptr<GameCore> gameCore)
{
	cout << "setting game core" << endl;
	cout << gameCore << endl;
	GAME_CORE_GLOBAL = gameCore;
	cout << GAME_CORE_GLOBAL << endl;
}

GameCore::GameCore(shared_ptr<Core> core)
	: core(core),
	  worldManager(new WorldManager()),
	  scriptManager(new ScriptManager()),
	  settingsManager(new SettingsManager())
{
}

GameCore::~GameCore(void)
{
}

void GameCore::update()
{
	// std::cout << "updating" << std::endl;

	if(scriptManager) scriptManager->update();
	if(worldManager) worldManager->update();
}

shared_ptr<GameCore> GameCore::getThis()
{
	return shared_from_this();
}

shared_ptr<Core> GameCore::getCore()
{
	return shared_ptr<Core>(core);
}

void GameCore::setCore(shared_ptr<Core> core)
{
	this->core = core;
}

shared_ptr<WorldManager> GameCore::getWorldManager()
{
	return shared_ptr<WorldManager>(worldManager);
}

shared_ptr<ScriptManager> GameCore::getScriptManager()
{
	return shared_ptr<ScriptManager>(scriptManager);
}

shared_ptr<SettingsManager> GameCore::getSettingsManager()
{
	return shared_ptr<SettingsManager>(settingsManager);
}

