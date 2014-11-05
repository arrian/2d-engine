#include "Game.h"

Game::Game(PolycodeView *view) {
    core = new CocoaCore(view, 640,480,false,false, 0,0,60);
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default");
    
    gameCore = new GameCore(core);
}

Game::~Game() {
    delete gameCore;
    delete core;
}

bool Game::Update() {
    gameCore->update();
    return core->updateAndRender();
}

