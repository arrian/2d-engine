//
// Polycode template. Write your code here.
// 

#include "Game.h"


Game::Game(PolycodeView *view) {
    core = new CocoaCore(view, 640,480,false,false, 0,0,60);
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default");
    
    world = new World(core);

}

Game::~Game() {
    delete world;
}

bool Game::Update() {
    world->update();
    return core->updateAndRender();
}