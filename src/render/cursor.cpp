#include "cursor.h"
#include "../util/constants.h"

Cursor::Cursor(){
  x = 0;
  y = 0;
  h = FONT_SIZE;
  w = 20;
}

Pos Cursor::getCurrentLocation(){
  return {this->x, this->y};
}

Dimen Cursor::getCursorDimension(){
  return {this->w, this->h};
}

void Cursor::moveup(){
  y-=w;
  if(y<0) y =0;

}

void Cursor::moveright(){
  x+=h;
}

void Cursor::moveleft(){
  x-=h;
  if(x <0){
      x = 0;
    }
}

void Cursor::movedown(){
  y+=w;
}

int Cursor::getX() const{
  return this->x;
}

int Cursor::getW() const{
  return this->w;
}
int Cursor::getH() const{
  return this->h;
}
int Cursor::getY() const{
  return this->y;
}

void Cursor::setX(int x1){
  this->x = x1;
}
void Cursor::setY(int y1){
  this->y = y1;
}
void Cursor::setW(int w1){
  this->w = w1;
}
void Cursor::setH(int h1){
  this->h = h1;
}

SDL_Rect Cursor::getRect(){
  return {this->x,this->y, this->w,this->h};
}
