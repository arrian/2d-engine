#pragma once

#include <string>
#include <vector>
#include <sstream>

class StringUtil
{
public:
  static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
      elems.push_back(item);
    }
    return elems;
  }

  static std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
  }

  template<typename T> static std::string toString(T t)
  {
    std::stringstream ss;
    ss << t;
    return ss.str();
  }
};

