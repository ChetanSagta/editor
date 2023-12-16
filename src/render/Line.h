#pragma once

#include "TextRenderer.h"
#include <string>

class Line {
public:
  void updateContent(std::string content);
  void renderText(int x, int y);

private:
  int m_width;
  std::string m_content;
  TextRenderer m_textRenderer;
};
