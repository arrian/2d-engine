#pragma once

#include <string>
#include <memory>

#include <Box2D/Box2D.h>

#include "Shape.h"
#include "Position.h"
#include "Display.h"

class Interactive
{
public:
  Interactive(int id, std::string name, WorldPosition position, std::shared_ptr<Shape> shape)
    : id(id, this, DataType::INTERACTIVE),
      name(name),
      position(position),
      shape(shape),
      rotation(0.0),
      body(NULL)
  {
  }

  ~Interactive(void) {}

  void draw(Display* display)
  {
    shape->draw(display->getScreenPosition(position), rotation, display->getWorldScale());
  }

  void update(double elapsedSeconds)
  {
    if(!body) return;
    b2Vec2 pos(body->GetPosition());
    position.x = pos.x;
    position.y = pos.y;
    rotation = body->GetAngle();
  }

  void createPhysics(b2World* world)
  {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = position.toPhysicsPosition();
    bodyDef.angle = rotation;

    body = world->CreateBody(&bodyDef);
    shape->createDynamicPhysics(body, 1.0f, 0.3f, &id);

  }

private:
  Id id;
  std::string name;
  WorldPosition position;
  double rotation;
  std::shared_ptr<Shape> shape;
  b2Body* body;
};

