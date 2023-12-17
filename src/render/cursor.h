#pragma once

#include "../util/fontmanager.h"

class Cursor
{
public:
  Cursor();
  void setX(int);
  void setY(int);
  void setW(int);
  void setH(int);
  int getX() const;
  int getY() const;
  int getW() const;
  int getH() const;
  Pos getCurrentLocation();
  Dimen getCursorDimension();
  void moveup();
  void movedown();
  void moveright();
  void moveleft();
  SDL_Rect getRect();
 private:
  int x, y, w, h;
};
