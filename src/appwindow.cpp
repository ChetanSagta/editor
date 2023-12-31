#include "appwindow.h"
#include "handler/insertmodehandler.h"
#include "handler/normalmodehandler.h"
#include "util/constants.h"
#include "util/models.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <spdlog/spdlog.h>
#include <string>

AppWindow::AppWindow(std::string title, int x, int y, int width, int height)
    : m_mode{MODE::NORMAL}, eHandler{nullptr} {
  m_current_line = &lines.front();
  if (m_current_line == nullptr) {
    m_current_line = new Line();
  }
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
  std::string fontpath =
      "/home/chetan/.fonts/Iosevka Term Nerd Font Complete Mono.ttf";
  m_font_manager.set_font_path(fontpath, FONT_SIZE);
  textRenderer.set_font_manager(&m_font_manager);
  /*textRenderer.setFont(font.c_str(), FONT_SIZE);*/

  SDL_Rect src;
  src.x = 0;
  src.y = 0;
  src.w = surface->w;
  src.h = surface->h;

  /*SDL_RenderFillRect(m_renderer, &cursor);*/
  SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
  SDL_FreeSurface(surface);
  surface = nullptr;
  SDL_RenderCopy(m_renderer, texture, NULL, &src);
  /*SDL_Color fg = BLACK;*/
  /*SDL_SetRenderDrawColor(m_renderer, fg.r, fg.g, fg.b, SDL_ALPHA_OPAQUE);*/
  SDL_RenderPresent(m_renderer);
}

void AppWindow::updateCursor(int x, int y) {
  cursor.setX(x);
  cursor.setY(y);
}

AppWindow::~AppWindow() {
  SDL_Quit();
  m_window = nullptr;
  m_renderer = nullptr;
}

void AppWindow::eventLoop() {
  m_bufferedText = "";
  while (!quit) {
    handleEvent();
    renderCursor();
    // textRenderer.render_text(m_window, m_renderer, m_current_line->getText(), GREEN);
    // for(ulong i=0;i<lines.size();i++){
      // std::cout<<i<<" "<<lines[i].getText()<<std::endl;
    // }
  }
}

void AppWindow::renderCursor(){
  SDL_Rect rect = cursor.getRect();
  SDL_SetRenderDrawColor(m_renderer,GREEN.r, GREEN.g, GREEN.b, GREEN.a);
  SDL_RenderFillRect(m_renderer,&rect);
  SDL_RenderPresent(m_renderer);
}

void AppWindow::handleEvent() {
  SDL_Event e;
  if (m_mode == NORMAL) {
    eHandler = new NormalModeHandler();
  } else if (m_mode == INSERT) {
    eHandler = new InsertModeHandler();
  }
  eHandler->handle(&e, m_current_line, &quit, &m_mode,&cursor);
  if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_RETURN)){
    lines.push_back(*m_current_line);
    m_current_line = new Line();
    return;
  }
}
void AppWindow::readFile(std::string) {}
