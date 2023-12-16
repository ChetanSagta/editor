#pragma once
#include "render/Line.h"
#include "render/TextRenderer.h"
#include "handler/EventHandler.h"
#include "util/fontmanager.h"
#include "util/models.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

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
  FontManager m_font_manager;
  bool quit = false;
  bool read= false;
  std::string m_bufferedText="";
  MODE m_mode;
  void readFile(std::string file);
  Pos cursorPos;
  EventHandler* eHandler;
  TextRenderer textRenderer;
  SDL_Rect cursor;
  std::vector<Line> lines;
  friend class Line;
};
