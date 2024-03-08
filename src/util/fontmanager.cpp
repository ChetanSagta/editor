#include "fontmanager.h"
#include <spdlog/spdlog.h>

void FontManager::set_font_path(std::string font_path, int font_height){
  m_font = TTF_OpenFont(font_path.c_str(), font_height);
  if (m_font == nullptr) {
    SPDLOG_ERROR("Unable to open font! Error: {}\n", SDL_GetError());
    SDL_Quit();
    exit(1);
  }
};

TTF_Font* FontManager::get_font(){
  return this->m_font;
}

FontManager::FontManager(){

}

FontManager::~FontManager(){
  TTF_CloseFont(m_font);
}
