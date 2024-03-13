#include "cursor.h"
#include "../util/constants.h"
#include <spdlog/spdlog.h>

Cursor::Cursor(){
  this->m_x = 0;
  this->m_y = 0;
  this->m_h = FONT_SIZE;
  this->m_w = 3;
}

Pos Cursor::getCurrentLocation(){
  return {this->m_x, this->m_y};
}

Dimen Cursor::getCursorDimension(){
  return {this->m_w, this->m_h};
}

void Cursor::moveup(){
  this->m_y-=this->m_h;
  if(this->m_y<0) this->m_y =0;
}

void Cursor::moveright(){
  this->m_x+=this->m_w;
}

void Cursor::moveleft(){
  this->m_x-=this->m_w;
  if(this->m_x <0){
  this->m_x = 0;
  }
}

void Cursor::movedown(){
  this->m_y+=this->m_h;
}

int Cursor::getX() const{
  return this->m_x;
}

int Cursor::getW() const{
  return this->m_w;
}
int Cursor::getH() const{
  return this->m_h;
}
int Cursor::getY() const{
  return this->m_y;
}

void Cursor::setX(int x1){
  this->m_x = x1;
}
void Cursor::setY(int y1){
  this->m_y = y1;
}
void Cursor::setW(int w1){
  this->m_w = w1;
}
void Cursor::setH(int h1){
  this->m_h = h1;
}

void Cursor::set_last_line_height(int height){
  this->m_last_line_height = height;
}

SDL_Rect Cursor::getRect(){
  return {this->m_x,this->m_y, this->m_w,this->m_h};
}

void Cursor::moveToNextLine(){
  this->m_y = this->getY()+this->m_last_line_height;
  this->m_x = 0;
}

void Cursor::reset(){
  this->m_x = 0;
  this->m_y = 0;
}
