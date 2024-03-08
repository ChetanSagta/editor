#include "textrenderer.h"
#include "../util/constants.h"
#include "cursor.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <spdlog/spdlog.h>

void TextRenderer::set_font_manager(FontManager* fontmanager) {
  this->m_font_manager = fontmanager;
  this->m_font = this->m_font_manager->get_font();
}

void TextRenderer::render_text(SDL_Window *window, SDL_Renderer *renderer,
                               std::string text, SDL_Color fg, Cursor *cursor) {
  int wh = 0, wb = 0;
  SDL_GetWindowSize(window, &wb, &wh);
  SDL_Surface *surface = TTF_RenderText_Solid_Wrapped(m_font, text.c_str(), fg, wb);
  if (surface == nullptr) {
    SPDLOG_ERROR("Unable to create render text solid! Error: {}\n",
                 SDL_GetError());
  }
  
  SDL_Rect src;
  src.x = cursor->getX();
  src.y = cursor->getY();
  src.w = surface->w;
  src.h = surface->h;

  cursor->setX(cursor->getX()+surface->w);
  cursor->set_last_line_height(surface->h);

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  surface = nullptr;
  SDL_RenderCopy(renderer, texture, NULL, &src);
  if(texture != nullptr){
    SDL_DestroyTexture(texture);
  }
  SDL_SetRenderDrawColor(renderer, fg.r, fg.g, fg.b, SDL_ALPHA_OPAQUE);
  SDL_RenderPresent(renderer);
}

void TextRenderer::render_char(SDL_Renderer *renderer, char ch, SDL_Color fg,
                               Pos pos) {
  SDL_Surface *surface = TTF_RenderGlyph_Solid(m_font, ch, fg);
  if (surface == nullptr) {
    SPDLOG_ERROR("Unable to create render text solid! Error: {}\n",
                 SDL_GetError());
  }
  SDL_Rect src;
  src.x = pos.x;
  src.y = pos.y;
  src.w = surface->w;
  src.h = surface->h;

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  surface = nullptr;
  SDL_RenderCopy(renderer, texture, NULL, &src);
  if(texture != nullptr){
    SDL_DestroyTexture(texture);
  }
  SDL_SetRenderDrawColor(renderer, fg.r, fg.g, fg.b, SDL_ALPHA_OPAQUE);
  SDL_RenderPresent(renderer);
}
