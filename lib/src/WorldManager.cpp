#include "WorldManager.h"

WorldManager::WorldManager()
{
	scene = shared_ptr<PhysicsScene2D>(new PhysicsScene2D(0.1, 60));

	ScenePrimitive *shape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 1.0,0.05);
	shape->setColor(0.0,0.0,0.1,1.0);
	shape->setPosition(0, -0.3);
	scene->addPhysicsChild(shape, PhysicsScene2DEntity::ENTITY_RECT, true);	
	
	for(int i=0; i < 200; i++) {
		shape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 0.08,0.02);
		shape->setRoll(rand() % 360);
        shape->setColor(RANDOM_NUMBER, RANDOM_NUMBER, RANDOM_NUMBER, 1.0);
		shape->setPosition(-0.3 + (RANDOM_NUMBER*0.6), RANDOM_NUMBER);
		scene->addPhysicsChild(shape, PhysicsScene2DEntity::ENTITY_RECT, false);
	}
}

WorldManager::~WorldManager(void)
{

}

void WorldManager::update()
{

}
