#pragma once

#include <spdlog/spdlog.h>
#include <string>

class Line {
public:
  void updateContent(std::string content);
  void removeCharAtEnd();
  void removeCharsAtEnd(int count);
  void addCharsAtEnd(std::string characters);
  std::string getText();
  void setText(std::string);
  void print();

  void setWidth(int height);
  void setHeight(int width);
  int getWidth() const;
  int getHeight() const;
  int getLineNumber() const;
  void setLineNumber(const int);
  int getLastLineHeight() const;
  void setLastLineHeight(const int);
  int getLineHeight() const;
  void setLineHeight(const int);
private:
  int m_width;
  int m_height;
  int m_line_height = 0;
  std::string m_content;
  int m_line_number = 0;
  int m_last_line_height = 0;
};
