#pragma once

#include "Id.h"

class PhysicsContactListener : public b2ContactListener
{
public:
  virtual void BeginContact(b2Contact* contact)
  {
    b2Fixture* fixA = contact->GetFixtureA();
    b2Fixture* fixB = contact->GetFixtureB();
    Id* idA = static_cast<Id*>(fixA->GetUserData());
    Id* idB = static_cast<Id*>(fixB->GetUserData());

    if(!idA || !idB) return;//no user data

    if(DataType::equal(idA->getDataType(), DataType::PLAYER_FEET)) idA->getObject<Player>()->addContact();
    if(DataType::equal(idB->getDataType(), DataType::PLAYER_FEET)) idB->getObject<Player>()->addContact();

  }

  virtual void EndContact(b2Contact* contact)
  {
    b2Fixture* fixA = contact->GetFixtureA();
    b2Fixture* fixB = contact->GetFixtureB();
    Id* idA = static_cast<Id*>(fixA->GetUserData());
    Id* idB = static_cast<Id*>(fixB->GetUserData());

    if(!idA || !idB) return;//no user data

    if(DataType::equal(idA->getDataType(), DataType::PLAYER_FEET)) idA->getObject<Player>()->removeContact();
    if(DataType::equal(idB->getDataType(), DataType::PLAYER_FEET)) idB->getObject<Player>()->removeContact();
  }

  void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
  {
    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);
    if (worldManifold.normal.y < -0.5f)
    {
      contact->SetEnabled(false);
    }
  }

private:



};


















