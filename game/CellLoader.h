#pragma once

#include <string>

#include "Data.h"
#include "DataItem.h"
#include "StringUtil.h"
#include "ShapeType.h"
#include "Cell.h"
#include "Shape.h"
#include "ShapeRectangle.h"
#include "ShapeImage.h"
#include "ShapeImageAnimated.h"
#include "ShapeLine.h"
#include "ShapeLineStrip.h"
#include "ShapePoint.h"

#include "Json.h"
#include "JsonUtil.h"
#include "FileUtil.h"

class CellLoader
{
public:

  static std::shared_ptr<Cell> load(int xCell, int yCell, std::string worldPath, Data& data)
  {
    std::shared_ptr<Cell> cell(new Cell(xCell, yCell));

    JsonUtil json(worldPath);
    json_value* world = json.getRoot();

    json_value* name = JsonUtil::getChild(world, "name");
    json_value* cells = JsonUtil::getChild(world, "cells");

    for (json_value* cellIt = cells->first_child; cellIt; cellIt = cellIt->next_sibling)
    {
      json_value* index = JsonUtil::getChild(cellIt, "index");
      int xCurrentCell = JsonUtil::getChild(index, "x")->int_value;
      if(xCurrentCell != xCell) continue;
      int yCurrentCell = JsonUtil::getChild(index, "y")->int_value;
      if(xCurrentCell != yCell) continue;

      json_value* shapes = JsonUtil::getChild(cellIt, "shapes");

      for(json_value* shapeIt = shapes->first_child; shapeIt; shapeIt = shapeIt->next_sibling)
      {
        //std::cout << "got shape" <<std::endl;
        DataItem item(data.get(JsonUtil::getChild(shapeIt, "id")->int_value));
        //std::cout << "data item " << item.dataType <<std::endl;
        Position position(JsonUtil::getPosition(JsonUtil::getChild(shapeIt, "p")));
        WorldPosition worldPosition(position, xCell, yCell);
        std::shared_ptr<Shape> shape(JsonUtil::getShape(item, position, shapeIt));
        
        addObject(cell, item, worldPosition, shape);
      }
    }

    //Creating cell ground
    for(std::vector<std::shared_ptr<Ground> >::iterator it = cell->ground.begin(); it != cell->ground.end(); ++it)
    {
      (*it)->createPhysics(cell->staticBody);
    }

    return cell;
  }

  static void addObject(std::shared_ptr<Cell>& cell, DataItem item, WorldPosition position, std::shared_ptr<Shape> shape)
  {
    //std::cout << "got add object " << item.dataType <<std::endl;
    switch(item.dataType)
    {
    case DataType::INTERACTIVE_OBJECT:
      //std::cout << "added interactive object" <<std::endl;
      cell->interactives.push_back(std::shared_ptr<Interactive>(new Interactive(item.id, item.name, position, shape)));
      break;
    case DataType::INTERACTIVE_GROUND:
      //std::cout << "added interactive ground" <<std::endl;
      cell->ground.push_back(std::shared_ptr<Ground>(new Ground(item.id, item.name, position, shape)));
    }
  }
};