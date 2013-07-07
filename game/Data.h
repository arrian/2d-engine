#pragma once

#include <map>

#include "DataItem.h"
#include "StringUtil.h"
#include "DataType.h"
#include "ShapeType.h"
#include "JsonUtil.h"

#include "Settings.h"//temp globals

class Data
{
public:
  Data(std::string path) 
    : items()
  {
    load(path);
  }

  ~Data(void) {}

  DataItem get(int id) {return items[id];}

private:
  std::map<int, DataItem> items;
  ShapeType shapeLib;
  DataType dataLib;

  void load(std::string path)
  {
    JsonUtil json(path);
    json_value* data = json.getRoot();

    recursiveAdd(data, DataType::ALL);
  }

  void recursiveAdd(json_value* node, DataType::Type dataType)
  {
    if(!node)
    {
      std::cout << "null node" << std::endl;
      return;
    }

    json_value* childrenJson = JsonUtil::getChild(node, "children");

    json_value* nameJson = JsonUtil::getChild(node, "name");
    if(!nameJson)
    {
      std::cout << "null nameJson" << std::endl;
      return;
    }
    std::string name(nameJson->string_value);

    if(childrenJson)//found a branch
    {
      for(json_value* child = childrenJson->first_child; child; child = child->next_sibling)
      {
        recursiveAdd(child, dataLib.stringToDataType(name));
      }
    }
    else//found a leaf
    {
      json_value* idJson = JsonUtil::getChild(node, "id");
      if(!idJson)
      {
        std::cout << "null idJson" << std::endl;
        return;
      }
      int id = idJson->int_value;
      
      json_value* shapeTypeJson = JsonUtil::getChild(node, "type");

      if(!shapeTypeJson)
      {
        std::cout << "null shapeTypeJson" << std::endl;
        return;
      }

      ShapeType::Type shapeType(shapeLib.stringToDataType(shapeTypeJson->string_value));

      json_value* resourcesJson = JsonUtil::getChild(node, "resources");

      std::vector<std::string> resources = std::vector<std::string>();
      if(resourcesJson)
      {
        for(json_value* resource = resourcesJson->first_child; resource; resource = resource->next_sibling)
        {
          resources.push_back(RESOURCE_PATH + std::string(resource->string_value));
        }
      }

      items.insert(std::pair<int,DataItem>(id, DataItem(id, name, shapeType, dataType, resources)));
    } 
  }
};

