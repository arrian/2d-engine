#pragma once

#include <stdexcept>

class FactoryException : public std::runtime_error
{
public:
  FactoryException(std::string message)
    : std::runtime_error("An internal exception occurred. " + message)
  {

  }



};