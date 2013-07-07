#pragma once

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"

#include "Position.h"
#include "Settings.h"

class Display
{
public:
  Display(ALLEGRO_DISPLAY* display)
    : display(display),
      worldPosition(CELL_SIZE / 2, CELL_SIZE / 2, 0, 0),
      worldScale(DEFAULT_WORLD_SCALE)
  {
    height = al_get_display_height(display);
    width = al_get_display_width(display);
    xScreenCentre = (int) (width / 2);
    yScreenCentre = (int) (height / 2);

    updateWorldPositions();
  }

  ~Display()
  {

  }

  WorldPosition getWorldPosition(ScreenPosition position)//TODO: seems incorrect
  {
    double xWorldSpace = (position.x - xScreenCentre) / worldScale;
    double yWorldSpace = (position.y - yScreenCentre) / worldScale;
    yWorldSpace = -yWorldSpace;//need to invert due to coordinate systems
    WorldPosition wPosition(worldPosition.x + xWorldSpace, worldPosition.y + yWorldSpace, worldPosition.xCell, worldPosition.yCell);
    wPosition.localise();
    return wPosition;
  }

  ScreenPosition getScreenPosition(WorldPosition position)
  {
    double xDiff = position.x - worldPosition.x;//delta from x centre
    double yDiff = position.y - worldPosition.y;//delta from y centre

    int xCellDiff = position.xCell - worldPosition.xCell;//cell x diff
    int yCellDiff = position.yCell - worldPosition.yCell;//cell y diff

    xDiff += (xCellDiff * CELL_SIZE);
    yDiff += (yCellDiff * CELL_SIZE);

    xDiff *= worldScale;
    yDiff *= worldScale;

    yDiff = -yDiff;//invert y axis

    return ScreenPosition(xDiff + xScreenCentre, yDiff + yScreenCentre);
  }

  /**
   * Translates the view of the world by the screen vector amount.
   */
  void translateScreen(int tx, int ty)
  {
    worldPosition += getWorldPosition(ScreenPosition(xScreenCentre + tx, yScreenCentre + ty));
    updateWorldPositions();
  }

  WorldPosition getScreenCentreWorldPosition()
  {
    return worldPosition;
  }

  void setWorldScale(double scale)
  {
    worldScale = scale;
  }

  double getWorldScale()
  {
    return worldScale;
  }

  int getXMinCell()
  {
    return tlWorldPosition.xCell;
  }

  int getXMaxCell()
  {
    return brWorldPosition.xCell;
  }

  int getYMaxCell()
  {
    return tlWorldPosition.yCell;
  }

  int getYMinCell()
  {
    return brWorldPosition.yCell;
  }

  WorldPosition getScreenBottomRightWorldPosition()
  {
    return brWorldPosition;
  }

  WorldPosition getScreenTopLeftWorldPosition()
  {
    return tlWorldPosition;
  }

  void setDisplayCentre(WorldPosition position)
  {
    this->worldPosition = position;
  }

private:
  ALLEGRO_DISPLAY* display;

  int height;
  int width;

  int xScreenCentre;
  int yScreenCentre;

  WorldPosition worldPosition;//the world position at the centre of the screen
  WorldPosition brWorldPosition;
  WorldPosition tlWorldPosition;
  double worldScale;

  void updateWorldPositions()
  {
    brWorldPosition = getWorldPosition(ScreenPosition(width, height));
    tlWorldPosition = getWorldPosition(ScreenPosition(0,0));
  }
};





