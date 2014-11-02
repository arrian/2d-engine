#pragma once

#include "DataType.h"

class Id
{
public:
  Id(void* object = NULL, DataType::Type type = DataType::NONE) 
    : id(globalId++),
      type(type),
      object(object)
  {

  }

  Id(int constantId, void* object = NULL, DataType::Type type = DataType::NONE) 
    : id(constantId),
    type(type),
    object(object)
  {
  
  }

  virtual ~Id() {}

  int getId() { return id; }
  DataType::Type getDataType() {return type;}
  
  template<class T>
  T* getObject() { return static_cast<T*>(object); }

private:
  int id;
  static int globalId;
  void* object;
  DataType::Type type;

  int getNewId() { return globalId; }
};

