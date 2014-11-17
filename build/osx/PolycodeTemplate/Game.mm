#include "Game.h"

#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"

Game::Game(PolycodeView *view)
	: core(new CocoaCore(view, 640,480,false,false, 8,8,60,-1,true)),
	  gameCore(new GameCore(core))
{
    std::cout << "entered Game constructor" << std::endl;
    
    boost::filesystem::path full_path( boost::filesystem::current_path() );
    
    std::cout << full_path << std::endl;
    
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default");
    
    core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYUP);
    
    GameCore::setGlobal(gameCore);
    shared_ptr<GameCore> testCore = GameCore::getGlobal();
    
    try
	{
		cout << "preparing directory" << endl;
		gameCore->getScriptManager()->execute("import sys\nsys.path.append('/Users/arrian/Dev/2d-engine/lib')");
		// scriptManager->execute("print(','.join(['test', 'blah', 'more']))");//"print(str(4*3))");//test python
		cout << "importing" << endl;
		gameCore->getScriptManager()->execute("import game\nprint(dir(game))");
		cout << "starting game core script" << endl;
		// scriptManager->setAttr("SCRIPT_MANAGER", sm);
		// python::scope().attr("SCRIPT_MANAGER") = getScriptManager();
		cout << "set script manager" << endl;
		gameCore->getScriptManager()->execute("print(','.join(['test', 'blah', 'more']))");//"print(str(4*3))");//test python
		gameCore->getScriptManager()->execute("printString='hello!'\ncommand='print(\"' + printString + '\")'\ngame.GameCore.get_global().get_script_manager().execute(command)");
		cout << "finished executing" << endl;
		//import sys\nsys.path.insert(0, '')\n
	}
	catch(...)//python::error_already_set &)
	{
		cout << "got error" << endl;
		cout << gameCore->getScriptManager()->getError() << endl;
	}
}

Game::~Game()
{
}

bool Game::update()
{
    gameCore->update();
    return core->updateAndRender();
}

void Game::handleEvent(Event *e)
{
    
    if(e->getDispatcher() == core->getInput())
    {
        InputEvent* inputEvent = (InputEvent*) e;
        std::cout << e->getEventType().getSTLString() << " " << e->getEventCode() << " " << inputEvent->key << std::endl;
        
    }
}
