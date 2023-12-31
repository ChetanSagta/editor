#include "line.h"
#include <spdlog/spdlog.h>
#include<iostream>

void Line::updateContent(std::string content) { this->m_content = content; }

void Line::renderText(int, int) {
  /*this->m_textRenderer.render_text(m_window, m_surface,*/
}

void Line::renderText(){
}

void Line::removeChars(int count) {
  if (count <= (int)m_content.length()) {
    for (int i = 0; i <= count; i++) {
      removeChar();
    }
  }
}

void Line::removeChar() {
  int length = m_content.length();
  if (length > 0)
    m_content.substr(0, length - 1);
}

void Line::addChars(std::string characaters){
  m_content.append(characaters);
}

void Line::print(){
  std::cout<<m_content<<std::endl;
}

std::string Line::getText(){
  return m_content;
}

void Line::setWidth(int width){
  this->m_width = width;
}
void Line::setHeight(int height){
  this->m_height = height;
}
int Line::getWidth() const{
  return this->m_width;
}
int Line::getHeight() const{
  return this->m_height;
}
