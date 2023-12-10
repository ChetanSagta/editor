#include "TextRenderer.h"
#include "util/constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <spdlog/spdlog.h>

void TextRenderer::setFont(std::string font_path, const int font_height = 24) {
  m_font = TTF_OpenFont(font_path.c_str(), font_height);
  if (m_font == nullptr) {
    SPDLOG_ERROR("Unable to open font! Error: {}\n", SDL_GetError());
    SDL_Quit();
    exit(1);
  }
  int success = TTF_SizeUTF8(m_font, "", &m_current_x, &m_current_y);
  if (success == -1) {
    SPDLOG_ERROR("Unable to find font size! Error: {}\n", TTF_GetError());
  }
}

Pos TextRenderer::getFontDimension(){
  return {m_current_x, m_current_y};
}

void TextRenderer::render_text(SDL_Window *window, SDL_Renderer *renderer, std::string text, SDL_Color fg) {
  int wh = 0, wb = 0, x = 0, y = 0;
  SDL_GetWindowSize(window, &wb, &wh);
  for (ulong i = 0; i < text.length(); i++) {
    x += m_current_x;
    if (x > wb) {
      y += m_current_y;
      x = 0;
    }
    render_char(renderer, text[i], fg, {x,y});
  }
}

void TextRenderer::render_char(SDL_Renderer *renderer, char ch, SDL_Color fg,
                               Pos pos) {
  SDL_Surface *surface = TTF_RenderGlyph32_Solid(m_font, ch, BLUE);
  if (surface == nullptr) {
    SPDLOG_ERROR("Unable to create render text solid! Error: {}\n",
                 SDL_GetError());
  }
  int success = TTF_SizeUTF8(m_font, &ch, &m_current_x, &m_current_y);
  if (success == -1) {
    SPDLOG_ERROR("Unable to find font size! Error: {}\n", TTF_GetError());
  }
  SDL_Rect src;
  src.x = pos.x;
  src.y = pos.y;
  src.w = m_current_x;
  src.h = m_current_y;

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  surface = nullptr;
  SDL_RenderCopy(renderer, texture, NULL, &src);
  SDL_SetRenderDrawColor(renderer, fg.r, fg.g, fg.b, SDL_ALPHA_OPAQUE);
  SDL_RenderPresent(renderer);
}
