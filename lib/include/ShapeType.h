#pragma once

#include <string>
#include <map>
#include "MapUtil.h"

class ShapeType
{
public:
  ShapeType()
  {
    MapUtil().map_init(StringToDataType)
      (std::string("NONE"), NONE)
      (std::string("RECTANGLE"), RECTANGLE)
      (std::string("LINE"), LINE)
      (std::string("LINE_STRIP"), LINE_STRIP)
      (std::string("POINT"), POINT)
      (std::string("IMAGE"), IMAGE)
      (std::string("IMAGE_ANIMATED"), IMAGE_ANIMATED);
  }

  enum Type
  {
    NONE,
    RECTANGLE,
    LINE,
    LINE_STRIP,
    POINT,
    IMAGE,
    IMAGE_ANIMATED
  };

  Type stringToDataType(std::string key)
  {
    if(StringToDataType.count(key) == 0) return ShapeType::NONE;
    return StringToDataType[key];
  }

private:

  std::map<std::string, Type> StringToDataType;

};


