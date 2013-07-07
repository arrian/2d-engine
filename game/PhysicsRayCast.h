#pragma once

#include <Box2D/Box2D.h>

class PhysicsRayCast : public b2RayCastCallback
{
public:
  PhysicsRayCast(b2World* world)
    : world(world)
  {
  }

  bool cast(b2Vec2 from, b2Vec2 to, DataType::Type ignore = DataType::NONE)
  {
    this->ignore = ignore;
    world->RayCast(this, from, to);
    if(hit) distance = (fraction * (to - from)).Length();
  }

  float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
  {
    Id* id = static_cast<Id*>(fixture->GetUserData());
    if(id == NULL) return 1;
    if(id->getDataType() & ignore) return 1;
    
    this->point = point;
    this->normal = normal;
    this->object = id;
    this->hit = true;
    this->fraction = fraction;

    return fraction;
  }

  
private:
  b2World* world;
  float distance;
  float fraction;
  b2Vec2 point;
  b2Vec2 normal;
  bool hit;
  Id* object;
  DataType::Type ignore;

};


