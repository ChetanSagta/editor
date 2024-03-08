#pragma once

#include "models.h"
#include <SDL2/SDL_ttf.h>
#include<string>
class FontManager{

public:
  void set_font_path(std::string, int font_height);
  TTF_Font* get_font();
  FontManager();
  ~FontManager();

private:
  TTF_Font* m_font;
  std::string m_font_path;
};
