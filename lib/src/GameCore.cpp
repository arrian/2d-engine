#include "GameCore.h"

GameCore::GameCore(shared_ptr<Core> core)
	: core(core),
	  worldManager(new WorldManager()),
	  scriptManager(new ScriptManager()),
	  settingsManager(new SettingsManager())
{
	try
	{
		cout << "importing" << endl;
		scriptManager->import("game");
		cout << "starting game core script" << endl;
		python::scope().attr("SCRIPT_MANAGER") = getScriptManager();
		cout << "set script manager" << endl;
		scriptManager->execute("print(','.join(['test', 'blah', 'more']))");//"print(str(4*3))");//test python
		scriptManager->execute("SCRIPT_MANAGER.execute('print('hello!')')");
		cout << "finished executing" << endl;
		//import sys\nsys.path.insert(0, '')\n
	}
	catch(...)//python::error_already_set &)
	{
		cout << "got error" << endl;
		cout << scriptManager->getError() << endl;
	}
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

