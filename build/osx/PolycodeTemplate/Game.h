#pragma once

#include <memory>
using std::shared_ptr;

#include <Polycode.h>
#import "PolycodeView.h"
using namespace Polycode;

#include "GameCore.h"

class Game {
public:
    Game(PolycodeView *view);
    ~Game();
    
    bool Update();

private:
    shared_ptr<Core> core;
    shared_ptr<GameCore> gameCore;
};