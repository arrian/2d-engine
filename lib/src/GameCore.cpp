#include "GameCore.h"

GameCore::GameCore(Core* core)
	: core(core)
{
}

GameCore::~GameCore(void)
{
}

void GameCore::update()
{
	std::cout << "updating" << std::endl;

}

Core* GameCore::getCore()
{
	return core;
}

WorldManager* GameCore::getWorldManager()
{
	return &worldManager;
}

ScriptManager* GameCore::getScriptManager()
{
	return &scriptManager
}

SettingsManager* GameCore::getSettingsManager()
{
	return &settingsManager;
}

