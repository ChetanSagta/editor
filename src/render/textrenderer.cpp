#include "textrenderer.h"
#include "../util/constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <spdlog/spdlog.h>

void TextRenderer::set_font_manager(FontManager* fontmanager) {
  this->m_font_manager = fontmanager;
  this->m_font = this->m_font_manager->get_font();
}

Pos TextRenderer::getFontDimension() { return {m_current_x, m_current_y}; }

void TextRenderer::render_text(SDL_Window *window, SDL_Renderer *renderer,
                               std::string text, SDL_Color fg) {
  int wh = 0, wb = 0, x = 0, y = 0;
  SDL_GetWindowSize(window, &wb, &wh);
  for (ulong i = 0; i < text.length(); i++) {
    x += m_current_x;
    if (x > wb) {
      y += m_current_y;
      x = 0;
    }
    render_char(renderer, text[i], fg, {x, y});
  }
}

void TextRenderer::render_char(SDL_Renderer *renderer, char ch, SDL_Color fg,
                               Pos pos) {
  SDL_Surface *surface = TTF_RenderGlyph_Solid(m_font, ch, fg);
  if (surface == nullptr) {
    SPDLOG_ERROR("Unable to create render text solid! Error: {}\n",
                 SDL_GetError());
  }
  m_current_x = surface->w;
  m_current_y = surface->h;
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
