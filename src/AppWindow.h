#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

class AppWindow {
public:
  AppWindow(std::string, int, int, int, int);
  ~AppWindow();
  void setSurface(SDL_Surface *surface);
  void eventLoop();
  void writeText();

private:
  SDL_Window *m_window;
  SDL_Surface *m_surface;
  SDL_Renderer *m_renderer;
  SDL_Texture *m_texture;
  TTF_Font *m_font;
  SDL_Rect Message_rect;
  bool quit = false;
};
