#pragma once


#include <windows.h>
#include <string>
#include <iostream>

#include "Settings.h"

class FileUtil
{
public:

  //TODO: add cross platform method of getting the current executable directory
  static std::string getExecutablePath() {
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
  }

  static std::string getImagePath()
  {
    return getExecutablePath() + RESOURCE_PATH + IMAGE_FOLDER;
  }

  static std::string getDataFile()
  {
    return getExecutablePath() + RESOURCE_PATH + DATA_FOLDER + DATA_FILE;
  }

  static std::string getWorldFile()
  {
    return getExecutablePath() + RESOURCE_PATH + WORLD_FOLDER + WORLD_FILE;
  }
};



