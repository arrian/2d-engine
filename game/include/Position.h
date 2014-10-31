#pragma once

#include <math.h>

#include <Box2D/Common/b2Draw.h>

#include "Settings.h"

/**
 * Defines a generic cell position.
 */
struct Position
{
  double x;
  double y;

  Position()
    : x(0),
      y(0)
  {
  }

  Position(float x, float y)
    : x(x),
      y(y)
  {
  }
};


/**
 * Defines a point within the world.
 */
struct WorldPosition
{
public:
  double x;
  double y;
  int xCell;
  int yCell;

  WorldPosition()
    : x(0.0),
      y(0.0),
      xCell(0),
      yCell(0)
  {
  }

  WorldPosition(double x, double y, int xCell, int yCell)
    : x(x),
      y(y),
      xCell(xCell),
      yCell(yCell)
  {
  }

  WorldPosition(b2Vec2 vec, int xCell, int yCell)
    : x(vec.x),
      y(vec.y),
      xCell(xCell),
      yCell(yCell)
  {
  }

  WorldPosition(Position position, int xCell, int yCell)
    : x(position.x),
      y(position.y),
      xCell(xCell),
      yCell(yCell)
  {
  }

  WorldPosition& operator+=(const WorldPosition& rhs) {
    x += rhs.x;
    y += rhs.y;
    xCell += rhs.xCell;
    yCell += rhs.yCell;
    localise();
    return *this;
  }

  b2Vec2 toPhysicsPosition()
  {
    return b2Vec2((float) x, (float) y);
  }

  /**
   * Localises stray world positions to their actual cell.
   */
  void localise()
  {
    if(x > CELL_SIZE)
    {
      xCell += (int) ((x / (double) CELL_SIZE) + 0.5);
      x = fmod(x, CELL_SIZE);
    }
    else if(x < 0)
    {
      xCell = -(1 + xCell - (int) ((x / (double) CELL_SIZE) + 0.5));
      x = fmod(x, CELL_SIZE) + CELL_SIZE;
    }

    if(y > CELL_SIZE)
    {
      yCell += (int) ((y / (double) CELL_SIZE) + 0.5);
      y = fmod(y, CELL_SIZE);
    }
    else if(y < 0)
    {
      yCell = -(1 + yCell - (int) ((y / (double) CELL_SIZE) + 0.5));
      y = fmod(y, CELL_SIZE) + CELL_SIZE;
    }


    /*        
    if(x > Cell.CELL_SIZE)
    {
    index.setX(index.getX() + (int) Math.round((x / Cell.CELL_SIZE)));
    x = x % Cell.CELL_SIZE;
    }
    else if(x < 0)
    {
    index.setX(-(1 + index.getX() - (int) Math.round((x / Cell.CELL_SIZE))));
    x = x % Cell.CELL_SIZE + Cell.CELL_SIZE;
    }

    if(y > Cell.CELL_SIZE)
    {
    index.setY(index.getY() + (int) Math.round((y / Cell.CELL_SIZE)));
    y = y % Cell.CELL_SIZE;
    }
    else if(y < 0)
    {
    index.setY(-(1 + index.getY() - (int) Math.round((y / Cell.CELL_SIZE))));
    y = y % Cell.CELL_SIZE + Cell.CELL_SIZE;
    }*/






    /*old
    if(x > CELL_SIZE || x < 0)
    {
      xCell += (int)((x / (double) CELL_SIZE) + 0.5);//add 0.5 to ensure correct rounding
      x = fmod(x, CELL_SIZE);
    }
    if(y > CELL_SIZE || y < 0)
    {
      yCell += (int)((y / (double) CELL_SIZE) + 0.5);//add 0.5 to ensure correct rounding
      y = fmod(y, CELL_SIZE);
    }*/
  }


};

/**
 * Defines a point on the screen.
 */
struct ScreenPosition
{
  float x;
  float y;

  ScreenPosition()
    : x(0),
      y(0)
  {
  }

  ScreenPosition(float x, float y)
    : x(x),
      y(y)
  {
  }
};


