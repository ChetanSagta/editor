#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<string>
#include "util/models.h"

class TextRenderer{
public:
  void setFont(std::string font_path, int font_height);
  void render_char(SDL_Renderer* renderer, char ch, SDL_Color fg,Pos pos);
  void render_text(SDL_Window* window, SDL_Renderer *renderer, std::string text, SDL_Color fg);

private:
  TTF_Font *m_font;
  int m_current_x, m_current_y;
};
