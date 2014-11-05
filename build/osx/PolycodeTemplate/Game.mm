#include "Game.h"

Game::Game(PolycodeView *view)
	: core(new CocoaCore(view, 640,480,false,false, 0,0,60)),
	  gameCore(new GameCore(core))
{
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default");
}

Game::~Game()
{
}

bool Game::Update()
{
    gameCore->update();
    return core->updateAndRender();
}

