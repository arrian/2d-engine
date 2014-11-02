#pragma once

#include <vector>
#include <iostream>

#include "Player.h"
#include "Ground.h"
#include "Climbable.h"
#include "Interactive.h"
#include "Dynamic.h"
#include "Static.h"
#include "Sky.h"
#include "Settings.h"

#include <Box2D/Box2D.h>
#include "PhysicsDebugDraw.h"
#include "PhysicsContactListener.h"
#include "PhysicsRayCast.h"

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"


class CellLoader;

class Cell
{
public:
  Cell(int x, int y)
    : x(x),
      y(y),
      world(b2Vec2(DEFAULT_GRAVITY)),
      debugDraw(x,y),
      player(NULL),
      contactListener(),
      rayCast(&world)
  {
    //Setting up debug draw
    world.SetDebugDraw(&debugDraw);
    debugDraw.SetFlags(b2Draw::e_shapeBit);

    //Setting up static bodies
    b2BodyDef staticBodyDef;
	  staticBodyDef.position.Set(0.0f, 0.0f);
	  staticBody = world.CreateBody(&staticBodyDef);

    world.SetContactListener(&contactListener);
  }

  ~Cell(void) {}

  void update(double elapsedSeconds)
  {
    world.Step((float) elapsedSeconds, 6, 2);

    for(std::vector<std::shared_ptr<Interactive> >::iterator iter = interactives.begin(); iter != interactives.end(); ++iter)
    {
      (*iter)->update(elapsedSeconds);
    }
  }

  void draw(Display* display)
  {
    for(std::vector<std::shared_ptr<Interactive> >::iterator it = interactives.begin(); it != interactives.end(); ++it) (*it)->draw(display);
    for(std::vector<std::shared_ptr<Ground> >::iterator it = ground.begin(); it != ground.end(); ++it) (*it)->draw(display);//debug
    //std::cout << body->GetPosition().x << "," << body->GetPosition().y << std::endl;
    
    debugDraw.setDisplay(display);
    //world.DrawDebugData();


    ScreenPosition topLeft(display->getScreenPosition(WorldPosition(0,0,x,y)));
    ScreenPosition bottomRight(display->getScreenPosition(WorldPosition(CELL_SIZE,CELL_SIZE,x,y)));
    al_draw_rectangle(topLeft.x,topLeft.y,bottomRight.x,bottomRight.y,al_map_rgb(0,0,255),2);
  }

  void addPlayer(Player* player)
  {
    this->player = player;
    player->createPhysics(&world);
  }

  void addRectangle(WorldPosition position)
  {
    std::shared_ptr<Interactive> rectangle(new Interactive(-1, "box", position, std::shared_ptr<Shape>(new ShapeRectangle(1, 1))));
    interactives.push_back(rectangle);
    rectangle->createPhysics(&world);
  }

private:

  Player* player;

  int x;
  int y;

  Sky sky;

  std::vector<std::shared_ptr<Ground> > ground;
  std::vector<std::shared_ptr<Climbable> > climbable;
  std::vector<std::shared_ptr<Interactive> > interactives;

  std::vector<std::shared_ptr<Dynamic> > sceneryDynamic;
  std::vector<std::shared_ptr<Static> > sceneryStatic;

  friend class CellLoader;

  //Physics
  PhysicsDebugDraw debugDraw;
  PhysicsContactListener contactListener;
  PhysicsRayCast rayCast;
  b2World world;
  b2Body* staticBody;
  
};

