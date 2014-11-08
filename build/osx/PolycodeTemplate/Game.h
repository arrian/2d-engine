#pragma once

#include <Polycode.h>
#import "PolycodeView.h"
using namespace Polycode;

#undef check
#include "GameCore.h"

class Game : public EventHandler
{
public:
    Game(PolycodeView *view);
    ~Game();
    
    bool update();
    void handleEvent(Event* event);

private:
    shared_ptr<Core> core;
    shared_ptr<GameCore> gameCore;
};