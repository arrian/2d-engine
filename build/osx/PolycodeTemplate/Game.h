#pragma once

#import "PolycodeView.h"
#include "Polycode.h"
#include "GameCore.h"

using namespace Polycode;

class Game {
public:
    Game(PolycodeView *view);
    ~Game();
    
    bool Update();
    
private:
    Core* core;
    GameCore* gameCore;
};