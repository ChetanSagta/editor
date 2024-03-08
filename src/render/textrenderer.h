#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<string>
#include "../util/models.h"
#include "../util/fontmanager.h"
#include "cursor.h"

class TextRenderer{
public:
  void set_font_manager(FontManager *fontManager);
  void render_char(SDL_Renderer* renderer, char ch, SDL_Color fg,Pos pos);
  void render_text(SDL_Window* window, SDL_Renderer *renderer, std::string text, SDL_Color fg, Cursor *cursor);
  void remove_char();
  void remove_chars(int count);

private:
  TTF_Font *m_font;
  FontManager* m_font_manager;
  int m_current_x, m_current_y;

};
