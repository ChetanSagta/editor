#include "../util/constants.h"
#include "line.h"
#include <spdlog/spdlog.h>
#include<iostream>

void Line::updateContent(std::string content) { this->m_content = content; }

void Line::removeCharsAtEnd(int count) {
  if (count <= (int)m_content.length()) {
    for (int i = 0; i <= count; i++) {
      removeCharAtEnd();
    }
  }
}

void Line::removeCharAtEnd() {
  int length = m_content.length();
  if (length > 0)
    m_content.substr(0, length - 1);
}

void Line::addCharsAtEnd(std::string characaters){
  m_content.append(characaters);
  m_line_height = characaters.size()%FONT_SIZE;
}

void Line::print(){
  SPDLOG_INFO("{}",m_content);
}

std::string Line::getText(){
  return m_content;
}

void Line::setText(const std::string text){
  this->m_content = text;
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

void Line::setLineNumber(const int line_number){
  this->m_line_number = line_number;
}

int Line::getLineNumber() const{
  return this->m_line_number;
}

void Line::setLastLineHeight(const int last_line_number){
  this->m_last_line_height= last_line_number;
}

int Line::getLastLineHeight() const{
  return this->m_last_line_height;
}

void Line::setLineHeight(const int line_height){
  this->m_line_height= line_height;
}

int Line::getLineHeight() const{
  return this->m_line_height;
}
