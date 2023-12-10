#include "AppWindow.h"
#include "TextRenderer.h"
#include "handler/InsertModeHandler.h"
#include "handler/NormalModeHandler.h"
#include "util/constants.h"
#include "util/models.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <spdlog/spdlog.h>
#include <string>

AppWindow::AppWindow(std::string title, int x, int y, int width, int height)
    : m_mode{MODE::NORMAL}, eHandler{nullptr} {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SPDLOG_INFO("Couldn't initialize SDL: {}\n", SDL_GetError());
    exit(1);
  }
  if (TTF_Init() < 0) {
    SPDLOG_INFO("Error initializing SDL_ttf: {}\n", TTF_GetError());
    exit(1);
  }
  m_window =
      SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_SHOWN);
  if (m_window == nullptr) {
    SPDLOG_ERROR("Unable to create window! Error: {}\n", SDL_GetError());
    exit(1);
  }
  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
  if (m_renderer == nullptr) {
    SPDLOG_ERROR("Unable to create renderer! Error: {}\n", SDL_GetError());
    exit(1);
  }

  SDL_Surface *surface = SDL_GetWindowSurface(m_window);
  std::string font =
      "/home/chetan/.fonts/Iosevka Term Nerd Font Complete Mono.ttf";
  textRenderer.setFont(font.c_str(), FONT_SIZE);
  cursorPos = textRenderer.getFontDimension();

  SDL_Rect src;
  src.x = 0;
  src.y = 0;
  src.w = surface->w;
  src.h = surface->h;

  cursor.x = 0;
  cursor.y = 0;
  SPDLOG_INFO("Cursor W: {}, H:{}", cursorPos.x, cursorPos.y);
  cursor.w = FONT_SIZE;
  cursor.h = cursorPos.y;

  SDL_RenderDrawRect(m_renderer, &cursor);
  SDL_FillRect(surface, &cursor, 255);
  /*SDL_RenderFillRect(m_renderer, &cursor);*/
  SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
  SDL_FreeSurface(surface);
  surface = nullptr;
  SDL_RenderCopy(m_renderer, texture, NULL, &src);
  SDL_Color fg = BLUE;
  SDL_SetRenderDrawColor(m_renderer, fg.r, fg.g, fg.b, SDL_ALPHA_OPAQUE);
  SDL_RenderPresent(m_renderer);
}

void AppWindow::updateCursor(int x, int y) {
  cursorPos.x = x;
  cursorPos.y = y;
}

AppWindow::~AppWindow() {
  SDL_Quit();
  m_window = nullptr;
  m_renderer = nullptr;
  m_font = nullptr;
}

void AppWindow::eventLoop() {
  m_bufferedText = "";
  while (!quit) {
    handleEvent();
    textRenderer.render_text(m_window, m_renderer, m_bufferedText, GREEN);
  }
}

void AppWindow::handleEvent() {
  SDL_Event e;
  if (m_mode == NORMAL) {
    eHandler = new NormalModeHandler();
  } else if (m_mode == INSERT) {
    eHandler = new InsertModeHandler();
  }
  eHandler->handle(e, m_bufferedText, &quit, &m_mode);
}
void AppWindow::readFile(std::string) {}
