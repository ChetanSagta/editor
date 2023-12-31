#pragma once
#include "render/line.h"
#include "render/textrenderer.h"
#include "handler/eventhandler.h"
#include "render/cursor.h"
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
  EventHandler* eHandler;
  TextRenderer textRenderer;
  Cursor cursor;
  std::vector<Line> lines;
  Line* m_current_line;
  friend class Line;

  void renderCursor();
};
