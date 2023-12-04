#include "TextRenderer.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <spdlog/spdlog.h>

void TextRenderer::setFont(std::string font_path, const int font_height = 24) {

  m_font = TTF_OpenFont(font_path.c_str(), font_height);
  if (m_font == nullptr) {
    SPDLOG_ERROR("Unable to open font! Error: {}\n", SDL_GetError());
    SDL_Quit();
    exit(1);
  }
}

void TextRenderer::set_font_dimen(int font_height, int font_width) {
  this->m_font_height = font_height;
  this->m_font_width = font_width;
}

void TextRenderer::render_char(SDL_Renderer *renderer, SDL_Texture *texture, char ch, SDL_Color fg, Pos pos) {
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

  /*SDL_Rect dst;*/
  /*dst.x = pos.x;*/
  /*dst.y = pos.y;*/
  /*src.w = surface->w;*/
  /*src.h = surface->h;*/

  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, &src);
  SDL_SetRenderDrawColor(renderer, fg.r, fg.g, fg.b, fg.a);
  /*SDL_SetRenderDrawColor(renderer, 0,0,0,0);*/
  SDL_RenderPresent(renderer);
}
