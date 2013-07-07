#pragma once

#include <Box2D/Box2D.h>

#include "Position.h"
#include "Display.h"
#include "ShapeRectangle.h"
#include "Id.h"
#include "DataType.h"

class Player
{
public:

  Player(WorldPosition position)
    : position(position),
      rectangle(0.5,1.7),
      body(NULL),
      feet(NULL),
      numberOfContacts(0),
      id(this, DataType::PLAYER),
      feetId(this, DataType::PLAYER_FEET),
      movingLeft(false),
      movingRight(false),
      movingDown(false),
      movingUp(false)
  {
  }

  ~Player(void)
  {
  }

  void draw(Display* display)
  {
    rectangle.draw(display->getScreenPosition(position), 0, display->getWorldScale());
  }

  WorldPosition getPosition()
  {
    return position;
  }

  void createPhysics(b2World* world)
  {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    b2Vec2 pos(position.toPhysicsPosition());
    bodyDef.position.Set(pos.x, pos.y);
    bodyDef.fixedRotation = true;

    body = world->CreateBody(&bodyDef);
    rectangle.createDynamicPhysics(body, 0.8f, 0.6f, &id);

    b2CircleShape circleShape;
    circleShape.m_radius = rectangle.getWidth() / 2;
    bodyDef.position.Set(position.x,position.y + (rectangle.getHeight() / 2));
    feet = world->CreateBody(&bodyDef);

    b2FixtureDef feetFixtureDef;
    feetFixtureDef.restitution = 0.0f;
    feetFixtureDef.density = 1.0f;
    feetFixtureDef.shape = &circleShape;
    feetFixtureDef.userData = &feetId;
    feet->CreateFixture(&feetFixtureDef);

    b2RevoluteJointDef jointDef;
    jointDef.bodyA = body;
    jointDef.bodyB = feet;
    jointDef.localAnchorA.Set(0, -(rectangle.getHeight() / 2));
    jointDef.localAnchorB.Set(0, 0);
    world->CreateJoint(&jointDef);
  }

  void setMovingLeft(bool left)
  {
    movingLeft = left;
  }

  void setMovingRight(bool right)
  {
    movingRight = right;
  }

  void setMovingUp(bool up)
  {
    movingUp = up;
  }

  void setMovingDown(bool down)
  {
    movingDown = down;
  }

  void stop()
  {
    stopHorizontal();
    stopVertical();
  }

  void jump()
  {
    if(numberOfContacts > 0) feet->ApplyLinearImpulse(b2Vec2(0, PLAYER_JUMP_STRENGTH), body->GetWorldCenter());
  }

  void update()
  {
    b2Vec2 vel = body->GetLinearVelocity();
    float desiredVel = 0;
    if(movingLeft) desiredVel = b2Max(vel.x - PLAYER_ACCELERATION, -PLAYER_MAX_VELOCITY);
    if(movingRight) desiredVel = b2Min(vel.x + PLAYER_ACCELERATION, PLAYER_MAX_VELOCITY);
    float velChange = desiredVel - vel.x;
    float impulse = body->GetMass() * velChange;
    if(numberOfContacts < 1) impulse *= 0.1f;
    body->ApplyLinearImpulse(b2Vec2(impulse,0), body->GetWorldCenter());

    b2Vec2 pos(body->GetPosition());
    position.x = pos.x;
    position.y = pos.y;
  }

  void addContact()
  {
    numberOfContacts++;
    if(numberOfContacts == 0) body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 0.0f));
  }

  void removeContact()
  {
    numberOfContacts--;
  }

private:

  Id id;
  Id feetId;

  WorldPosition position;
  b2Body* body;
  b2Body* feet;

  int numberOfContacts;
  bool movingLeft;
  bool movingRight;
  bool movingDown;
  bool movingUp;

  ShapeRectangle rectangle;

  void stopVertical()
  {
    movingDown = false;
    movingUp = false;
  }

  void stopHorizontal()
  {
    movingLeft = false;
    movingRight = false;
  }
};

