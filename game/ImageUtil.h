#pragma once

#include <string>
#include <map>
#include <iostream>

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"


struct ImageReference
{
  ALLEGRO_BITMAP* bitmap;
  std::string name;

 ImageReference(std::string name, ALLEGRO_BITMAP* bitmap)
   : bitmap(bitmap),
     name(name)
 {
 }
};

struct Image
{
  int referenceCount;
  ALLEGRO_BITMAP* bitmap;
};


class ImageUtil
{
public:

  static void release(std::string image)
  {
    if(images.count(image) > 0)
    {
      images[image].referenceCount--;
      if(images[image].referenceCount <= 0)
      {
        al_destroy_bitmap(images[image].bitmap);
        images.erase(images.find(image));
      }
    }
  }

  static ALLEGRO_BITMAP* acquire(std::string image)
  {
    if(images.count(image) > 0)
    {
      images[image].referenceCount++;
      //std::cout << "acquired " << image << " with " << images[image].referenceCount << " references " << std::endl;
      return images[image].bitmap;
    }

    std::cout << "loading new image " << image << std::endl;

    Image nImage;
    nImage.referenceCount = 1;
    nImage.bitmap = al_load_bitmap(image.c_str());

    if(!nImage.bitmap) throw std::exception("failed to load the given bitmap");

    images.insert(std::pair<std::string, Image>(image, nImage));
    return nImage.bitmap;
  }

private:
  static std::map<std::string, Image> images;

};





