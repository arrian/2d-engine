#pragma once

#include "ShapeType.h"
#include "DataType.h"


struct DataItem 
{
  int id;
  std::string name;
  ShapeType::Type shapeType;
  DataType::Type dataType;//the most detailed type that can be found
  std::vector<std::string> resources;

  DataItem()
    : id(-1),
      name("default"),
      shapeType(),
      dataType(DataType::NONE),
      resources()
  {
  }

  DataItem(int id, std::string name, ShapeType::Type shapeType, DataType::Type dataType, std::vector<std::string> resources) 
    : id(id),
      name(name),
      shapeType(shapeType),
      dataType(dataType),
      resources(resources)
  {
  }


};