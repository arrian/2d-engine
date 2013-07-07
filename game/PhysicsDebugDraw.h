#pragma once


#include <Box2D/Common/b2Draw.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"

#include "Display.h"

 class PhysicsDebugDraw : public b2Draw
  {
  public:

    PhysicsDebugDraw(int xCell, int yCell)
      : xCell(xCell),
        yCell(yCell)
    {
    }

    void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) 
    {
      for (int32 i = 1; i < vertexCount; i++)
      {
        DrawSegment(vertices[i - 1], vertices[i], color);
      }
      DrawSegment(vertices[vertexCount - 1], vertices[0], color);
    }

    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) 
    {
      DrawPolygon(vertices, vertexCount, color);
    }

    void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) 
    {
      ScreenPosition sp(display->getScreenPosition(WorldPosition(center.x, center.y, xCell, yCell)));
      al_draw_circle(sp.x, sp.y, radius * display->getWorldScale(), al_map_rgb(color.r, color.g, color.b), DEFAULT_LINE_WIDTH * display->getWorldScale()); 
    }

    void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) 
    {
      ScreenPosition sp(display->getScreenPosition(WorldPosition(center.x, center.y, xCell, yCell)));
      al_draw_filled_circle(sp.x, sp.y, radius * display->getWorldScale(), al_map_rgb(color.r, color.g, color.b)); 
    }

    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) 
    {
      ScreenPosition sp1(display->getScreenPosition(WorldPosition(p1, xCell, yCell)));
      ScreenPosition sp2(display->getScreenPosition(WorldPosition(p2, xCell, yCell)));
      al_draw_line(sp1.x, sp1.y, sp2.x, sp2.y, al_map_rgb(color.r, color.g, color.b), DEFAULT_LINE_WIDTH * display->getWorldScale());
    }

    void DrawTransform(const b2Transform& xf) 
    {
    }

    void setDisplay(Display* display)
    {
      this->display = display;
    }

    Display* display;
    int xCell;
    int yCell;
  };

