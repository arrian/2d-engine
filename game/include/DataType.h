#pragma once

#include <map>
#include <string>

#include "MapUtil.h"

class DataType
{
public:
  DataType()
  {
    MapUtil().map_init(StringToDataType)
      ("World", ALL)
      ("Creature", CREATURE)
      ("Creature Aggressive", CREATURE_AGGRESSIVE)
      ("Creature Passive", CREATURE_PASSIVE)
      ("Creature Interactive", CREATURE_INTERACTIVE)
      ("Interactive", INTERACTIVE)
      ("Interactive Climbable", INTERACTIVE_CLIMBABLE)
      ("Interactive Ceiling", INTERACTIVE_CEILING)
      ("Interactive Ground", INTERACTIVE_GROUND)
      ("Interactive Object", INTERACTIVE_OBJECT)
      ("Scenery", SCENERY)
      ("Scenery Dynamic", SCENERY_DYNAMIC)
      ("Scenery Static", SCENERY_STATIC)
      ("Player", PLAYER);
  }

  enum Type
  {
    NONE = 0,

    CREATURE = 1 << 0,
    CREATURE_AGGRESSIVE = 1 << 1 | CREATURE,
    CREATURE_INTERACTIVE = 1 << 2 | CREATURE,
    CREATURE_PASSIVE = 1 << 3 | CREATURE,

    INTERACTIVE = 1 << 4,
    INTERACTIVE_CLIMBABLE = 1 << 5 | INTERACTIVE,
    INTERACTIVE_GROUND = 1 << 6 | INTERACTIVE,
    INTERACTIVE_CEILING = 1 << 7 | INTERACTIVE,
    INTERACTIVE_OBJECT = 1 << 8 | INTERACTIVE,

    SCENERY = 1 << 9,
    SCENERY_STATIC = 1 << 10 | SCENERY,
    SCENERY_DYNAMIC = 1 << 11 | SCENERY,

    PLAYER = 1 << 12,
    PLAYER_FEET = 1 << 13 | PLAYER,

    ALL = ~0
  };

  Type stringToDataType(std::string key)
  {
    if(StringToDataType.count(key) == 0) return DataType::NONE;
    return StringToDataType[key];
  }

  static bool equal(DataType::Type left, DataType::Type right)
  {
    return left == right;
  }

  static bool grouped(DataType::Type left, DataType::Type right)
  {
    if(left & right) return true;
    return false;
  }

private:

  std::map<std::string, Type> StringToDataType;


};