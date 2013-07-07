
#include <Box2D/Box2D.h>

#include "ShapeLine.h"
#include "Id.h"
#include "DataType.h"


class Ground
{
public:
  Id id;
  WorldPosition position;
  std::shared_ptr<ShapeLine> shape;

  Ground(int id, std::string name, WorldPosition position, std::shared_ptr<Shape> shape)
    : position(position),
      shape(std::static_pointer_cast<ShapeLine>(shape)),
      id(this, DataType::INTERACTIVE_GROUND)
  {
  }

  void createPhysics(b2Body* staticBody)
  {
    shape->createStaticPhysics(position, staticBody, 0.0f, 0.0f, &id);
  }

  void draw(Display* display)
  {
    shape->draw(display->getScreenPosition(position), 0.0f, display->getWorldScale());
  }
};