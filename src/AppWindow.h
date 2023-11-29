#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

enum MODE{
  INSERT, 
  NORMAL, 
  VISUAL
};

class AppWindow {
public:
  AppWindow(std::string, int, int, int, int);
  ~AppWindow();
  void setSurface(SDL_Surface *surface);
  void eventLoop();
  void writeText();
  void handleEvent(SDL_Event);

private:
  SDL_Window *m_window;
  SDL_Surface *m_surface;
  SDL_Renderer *m_renderer;
  SDL_Texture *m_texture;
  TTF_Font *m_font;
  bool quit = false;
  bool read= false;
  std::string m_bufferedText=" ";
  int count = 0;
  MODE m_mode = MODE::NORMAL;
  void readFile(std::string file);
};
