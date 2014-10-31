#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Json.h"

#include "StringUtil.h"
#include "ShapeType.h"
#include "Shape.h"
#include "ShapeRectangle.h"
#include "ShapeImage.h"
#include "ShapeImageAnimated.h"
#include "ShapeLine.h"
#include "ShapeLineStrip.h"
#include "ShapePoint.h"


class JsonUtil
{
public:

  char* source;
  json_value* root;

  char *errorPos;
  char *errorDesc;
  int errorLine;
  block_allocator allocator;

  JsonUtil(std::string path)
    : allocator(1 << 10),
      errorPos(0),
      errorDesc(0),
      errorLine(0)
  {
    std::ifstream t(path);
    std::stringstream buffer;
    buffer << t.rdbuf();

    std::string file = buffer.str();

    source = new char[file.size() + 1];
    source[file.size()] = 0;
    memcpy(source,file.c_str(),file.size());

    root = json_parse(source, &errorPos, &errorDesc, &errorLine, &allocator);
  }

  ~JsonUtil()
  {
    delete[] source; 
  }

  json_value* getRoot()
  {
    return root;
  }

  static json_value* getChild(json_value* parent, std::string name)
  {
    if(!parent) throw std::runtime_error("could not get child of null parent node");
    for(json_value* childIt = parent->first_child; childIt; childIt = childIt->next_sibling)
    {
      if(std::string(childIt->name) == name) return childIt;
    }
    return NULL;
  }

  static Position getPosition(json_value* position)
  {
    float xPos = getChild(position, "x")->float_value;
    float yPos = getChild(position, "y")->float_value;
    return Position(xPos, yPos);
  }

  static std::shared_ptr<Shape> getShape(DataItem item, Position position, json_value* shapeIt)
  {
    std::shared_ptr<Shape> shape(NULL);

    switch(item.shapeType)
    {
    case ShapeType::RECTANGLE:
      {
        double width = getChild(shapeIt, "w")->float_value;
        double height = getChild(shapeIt, "h")->float_value;
        shape = std::shared_ptr<Shape>(new ShapeRectangle(width, height));
        break;
      }
    case ShapeType::LINE: 
      {
        json_value* vec = getChild(shapeIt, "v");
        double xVec = getChild(vec, "x")->float_value;
        double yVec = getChild(vec, "y")->float_value;
        shape = std::shared_ptr<Shape>(new ShapeLine(Position(xVec, yVec)));
        break;
      }
    case ShapeType::LINE_STRIP: 
      break;
    case ShapeType::IMAGE: 
      if(item.resources.size() == 0) throw std::runtime_error("no image found for image shape");
      shape = std::shared_ptr<Shape>(new ShapeImage(item.resources[0]));
      break;
    case ShapeType::IMAGE_ANIMATED: 
      if(item.resources.size() == 0) throw std::runtime_error("no images found for animated image shape");
      shape = std::shared_ptr<Shape>(new ShapeImageAnimated(Animations()));//TODO: get animations including states and frames
      break;
    case ShapeType::POINT:
      shape = std::shared_ptr<Shape>(new ShapePoint());
      break;
    default: break;
    } 
    return shape;
  }

};


