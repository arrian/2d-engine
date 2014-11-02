#pragma once

#ifdef _WIN32
#include <windows.h>
#else
#include <mach-o/dyld.h>
#endif

#include <string>
#include <iostream>

#include "Settings.h"

class FileUtil
{
public:

  //TODO: add cross platform method of getting the current executable directory

#ifdef _WIN32
  static std::string getExecutablePath() {
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
  }
#else
  static std::string getExecutablePath() {
    char buffer[MAX_PATH];
    uint32_t size = sizeof(buffer);
    if (_NSGetExecutablePath(buffer, &size) == 0)
    {
      std::string::size_type pos = std::string(buffer).find_last_of("\\/");
      return std::string(buffer).substr(0, pos);
      //printf("executable path is %s\n", buffer);
    }
    //else printf("buffer too small; need size %u\n", size); 
    throw std::runtime_error("Failed to get executable path.");
  }
#endif

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

  static std::string getFontPath()
  {
    return getExecutablePath() + RESOURCE_PATH + FONT_FOLDER;

  }
};



