#pragma once

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

#include "Shape.h"
#include "ImageUtil.h"

class ShapeImage : public Shape
{
public:
  ImageReference image;

  ShapeImage(std::string image)
    : image(image, ImageUtil::acquire(image))
  {
  }

  ~ShapeImage()
  {
    ImageUtil::release(image.name);
  }

  virtual void draw(ScreenPosition position, double rotation, double scale)
  { 
    double imageScale = scale * DEFAULT_IMAGE_SCALE;
    al_draw_scaled_rotated_bitmap(image.bitmap, 
      (float)al_get_bitmap_width(image.bitmap) / 2.0f, 
      (float)al_get_bitmap_height(image.bitmap) / 2.0f , 
      position.x,// - (al_get_bitmap_width(image.bitmap) / 2) * imageScale, 
      position.y - (al_get_bitmap_height(image.bitmap) / 2.0f) * imageScale, 
      imageScale, imageScale, rotation, 0);
  }
};




