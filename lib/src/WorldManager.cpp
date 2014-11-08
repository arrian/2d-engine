#include "WorldManager.h"

WorldManager::WorldManager()
{
	scene = shared_ptr<PhysicsScene2D>(new PhysicsScene2D(0.1, 60));

	ScenePrimitive *shape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 1.0,0.05);
	shape->setColor(0.0,0.0,0.1,1.0);
	shape->setPosition(0, -0.3);
	scene->addPhysicsChild(shape, PhysicsScene2DEntity::ENTITY_RECT, true);	
	
	ScenePrimitive *shape2 = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 0.05, 1.0);
	shape2->setColor(0.0,0.0,0.1,1.0);
	shape2->setPosition(-0.3, -0.4);
	shape2->setRoll(45);
	scene->addPhysicsChild(shape2, PhysicsScene2DEntity::ENTITY_RECT, true);	
	
	ScenePrimitive *shape3 = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 0.05, 1.0);
	shape3->setColor(0.0,0.0,0.1,1.0);
	shape3->setPosition(0.3, -0.4);
	shape3->setRoll(-45);
	scene->addPhysicsChild(shape3, PhysicsScene2DEntity::ENTITY_RECT, true);	
	
	// for(int i=0; i < 1000; i++) {
	// 	shape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 0.02,0.02);
	// 	shape->setRoll(rand() % 360);
 //        shape->setColor(RANDOM_NUMBER, RANDOM_NUMBER, RANDOM_NUMBER, 1.0);
	// 	shape->setPosition(-0.3 + (RANDOM_NUMBER*0.6), RANDOM_NUMBER);
	// 	scene->addPhysicsChild(shape, PhysicsScene2DEntity::ENTITY_RECT, false);
	// }
}

WorldManager::~WorldManager(void)
{

}

int count = 0;

void WorldManager::update()
{
	count++;

	if(count % 10 == 0) 
	{
		ScenePrimitive *shape;
		shape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 0.02,0.02);
		shape->setRoll(rand() % 360);
        shape->setColor(RANDOM_NUMBER, RANDOM_NUMBER, RANDOM_NUMBER, 1.0);
		shape->setPosition(-0.3 + (RANDOM_NUMBER*0.6), RANDOM_NUMBER);
		scene->addPhysicsChild(shape, PhysicsScene2DEntity::ENTITY_RECT, false);
	}
}
