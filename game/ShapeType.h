#pragma once

#include "MapUtil.h"

class ShapeType
{
public:
  ShapeType()
  {
    MapUtil().map_init(StringToDataType)
      ("NONE", NONE)
      ("RECTANGLE", RECTANGLE)
      ("LINE", LINE)
      ("LINE_STRIP", LINE_STRIP)
      ("POINT", POINT)
      ("IMAGE", IMAGE)
      ("IMAGE_ANIMATED", IMAGE_ANIMATED);
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


