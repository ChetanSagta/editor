#pragma once
#include "handler/eventhandler.h"
#include "handler/insertmodehandler.h"
#include "handler/normalmodehandler.h"
#include "render/cursor.h"
#include "render/line.h"
#include "render/textrenderer.h"
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
  void eventLoop();
  void handleEvent();

private:
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;
  SDL_Event m_event;
  FontManager m_font_manager;
  bool quit = false;
  bool read = false;
  MODE m_mode;
  void readFile(std::string file);
  EventHandler *eHandler;
  InsertModeHandler *m_iHandler;
  NormalModeHandler *m_nHandler;
  TextRenderer textRenderer;
  Cursor cursor;
  std::vector<Line> lines;
  Line *m_current_line;
  void renderCursor();
};
