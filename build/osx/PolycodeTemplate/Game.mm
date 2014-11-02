//
// Polycode template. Write your code here.
// 

#include "Game.h"


Game::Game(PolycodeView *view) {
    core = new CocoaCore(view, 640,480,false,false, 0,0,60);	  
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default");

	// Write your code here!
}

Game::~Game() {
    
}

bool Game::Update() {
    return core->updateAndRender();
}