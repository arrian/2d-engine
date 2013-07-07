#pragma once

#include <map>
#include <vector>

#include "Shape.h"

typedef std::map<int, std::vector<std::string> > Animations;
typedef std::map<int, std::vector<ImageReference> > AnimationsReference;

class ShapeImageAnimated : public Shape
{
public:

  ShapeImageAnimated(Animations animations)
    : animations()
  {
    for(Animations::iterator it = animations.begin(); it != animations.end(); ++it)
    {
      std::vector<ImageReference> ir;
      for(std::vector<std::string>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
      {
        ir.push_back(ImageReference(*it2, ImageUtil::acquire(*it2)));
      }
      this->animations.insert(std::pair<int, std::vector<ImageReference> >(it->first, ir));
    }
      
  }

  ~ShapeImageAnimated()
  {
    for(AnimationsReference::iterator it = animations.begin(); it != animations.end(); ++it) 
    {
      for(std::vector<ImageReference>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
      {
        ImageUtil::release(it2->name);
      }
    }
  }

  virtual void draw(ScreenPosition position, double rotation, double scale)
  {
    ALLEGRO_BITMAP* bitmap = animations[state][frame].bitmap;
    al_draw_scaled_rotated_bitmap(bitmap, 
      (float)al_get_bitmap_width(bitmap) / (float) 2, 
      (float)al_get_bitmap_height(bitmap) / (float) 2, 
      position.x - al_get_bitmap_width(bitmap) / 2, 
      position.y - al_get_bitmap_height(bitmap), 
      scale * DEFAULT_IMAGE_SCALE, scale * DEFAULT_IMAGE_SCALE, rotation, 0);
  }

  void setState(int state)
  {
    this->state = state;
    this->frame = 0;
  }

  void nextFrame()
  {
    frame++;
    if(frame >= getStateFrameCount(state)) frame = 0;
  }

  void previousFrame()
  {
    frame--;
    if(frame < 0) frame = getStateFrameCount(state) - 1;
  }

  int getStateFrameCount(int state)
  {
    if(animations.count(state) > 0) return animations[state].size();
    return 0;
  }

private:
  int state;
  int frame;

  AnimationsReference animations;
};




