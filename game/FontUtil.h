#pragma once

#include <string>
#include <map>
#include <iostream>

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"

#include "FileUtil.h"


struct FontReference
{
  ALLEGRO_FONT* font;
  std::string name;

  FontReference(std::string name, ALLEGRO_FONT* font)
    : font(font),
      name(name)
  {
  }
};

struct Font
{
  int referenceCount;
  ALLEGRO_FONT* font;
};


class FontUtil
{
public:

  static void release(std::string font)
  {
    if(fonts.count(font) > 0)
    {
      fonts[font].referenceCount--;
      if(fonts[font].referenceCount <= 0)
      {
        al_destroy_font(fonts[font].font);
        fonts.erase(fonts.find(font));
      }
    }
  }

  static ALLEGRO_FONT* acquire(std::string font)
  {
    if(fonts.count(font) > 0)
    {
      fonts[font].referenceCount++;
      return fonts[font].font;
    }

    std::cout << "loading new font " << font << std::endl;

    Font nFont;
    nFont.referenceCount = 1;
    nFont.font = al_load_ttf_font((FileUtil::getFontPath() + font).c_str(), 16, 0);//TODO add font size support

    if(!nFont.font) throw std::runtime_error("failed to load the given font");

    fonts.insert(std::pair<std::string, Font>(font, nFont));
    return nFont.font;
  }

private:
  static std::map<std::string, Font> fonts;

};


