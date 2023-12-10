#pragma once
#include "TextRenderer.h"
#include "handler/EventHandler.h"
#include "util/models.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class AppWindow {
public:
  AppWindow(std::string, int, int, int, int);
  ~AppWindow();
  void setSurface(SDL_Surface *surface);
  void eventLoop();
  void handleEvent();
  void updateCursor(int x, int y);

private:
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;
  TTF_Font *m_font;
  bool quit = false;
  bool read= false;
  std::string m_bufferedText=" ";
  MODE m_mode;
  void readFile(std::string file);
  Pos cursorPos;
  EventHandler* eHandler;
  TextRenderer textRenderer;
  SDL_Rect cursor;
};
