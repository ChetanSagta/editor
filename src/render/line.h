#pragma once

#include "textrenderer.h"
#include <string>

class Line {
public:
  void updateContent(std::string content);
  void renderText(int x, int y);
  void renderText();
  void removeCharAtEnd();
  void removeCharsAtEnd(int count);
  void addCharsAtEnd(std::string characters);
  std::string getText();
  void print();

  void setWidth(int height);
  void setHeight(int width);
  int getWidth() const;
  int getHeight() const;

private:
  int m_width;
  int m_height;
  std::string m_content;
  TextRenderer m_textRenderer;
};
