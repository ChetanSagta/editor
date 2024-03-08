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
  void moveToNextLine();
  void reset();
  SDL_Rect getRect();
  void set_last_line_height(int);
 private:
  int x, y, w, h;
  int last_line_height;
};
