#include "Game.h"

Game::Game(PolycodeView *view)
	: core(new CocoaCore(view, 640,480,false,false, 8,8,60,-1,true)),
	  gameCore(new GameCore(core))
{
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default");
    
    core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYUP);
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
