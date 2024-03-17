#include "appwindow.h"
#include "handler/insertmodehandler.h"
#include "handler/normalmodehandler.h"
#include "util/constants.h"
#include "util/models.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <exception>
#include <iostream>
#include <spdlog/spdlog.h>
#include <string>

AppWindow::AppWindow(std::string title, int x, int y, int width, int height)
    : m_mode{MODE::NORMAL}, eHandler{nullptr} {
  m_iHandler = new InsertModeHandler();
  m_nHandler = new NormalModeHandler();
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
  const std::string fontpath =
      "/home/chetan/.fonts/Iosevka Term Nerd Font Complete Mono.ttf";
  m_font_manager.set_font_path(fontpath, FONT_SIZE);
  textRenderer.set_font_manager(&m_font_manager);

  SDL_Rect src;
  src.x = 0;
  src.y = 0;
  src.w = surface->w;
  src.h = surface->h;

  SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
  SDL_FreeSurface(surface);
  surface = nullptr;
  SDL_RenderCopy(m_renderer, texture, NULL, &src);
  SDL_DestroyTexture(texture);
}

AppWindow::~AppWindow() {
  SDL_Quit();
  m_window = nullptr;
  m_renderer = nullptr;
}

void AppWindow::eventLoop() {
  while (!quit) {
    while (SDL_PollEvent(&m_event) != 0) {
      SDL_RenderClear(m_renderer);
      if (m_event.type == SDL_QUIT) {
        quit = true;
      } else {
        SDL_Keysym keysym = (m_event).key.keysym;
        switch (keysym.sym) {
        case SDLK_UP:
          cursor.moveup();
          break;
        case SDLK_DOWN:
          cursor.movedown();
          break;
        case SDLK_RIGHT:
          cursor.moveright();
          break;
        case SDLK_LEFT:
          cursor.moveleft();
          break;
        default:
          handleEvent();
          break;
        }
        Pos pos = {0, 0};
        for (size_t i = 0; i < lines.size(); i++) {
          Line *current_line = &lines.at(i);
          pos.x = 0;
          pos.y += current_line->getLastLineHeight();
          if (current_line->getText().length() > 0) {
            textRenderer.render_text(m_window, m_renderer, &lines.at(i), GREEN,
                                     &cursor, pos);
            cursor.setMaxY(pos.y);
          }
        }
        if (m_current_line->getText().size() > 0) {
          pos.x = 0;
          pos.y += m_current_line->getLastLineHeight();
          textRenderer.render_text(m_window, m_renderer, m_current_line, GREEN,
                                   &cursor, pos);
          cursor.setMaxY(pos.y);
        }
      }
    }
    cursor.setMaxX(m_current_line->getText().length());
    renderCursor();
    SDL_RenderPresent(m_renderer);
  }
}

void AppWindow::renderCursor() {
  SDL_Rect rect = cursor.getRect();
  SDL_SetRenderDrawColor(m_renderer, BLUE.r, BLUE.g, BLUE.b, BLUE.a);
  SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_ADD);
  SDL_RenderFillRect(m_renderer, &rect);
  SDL_SetRenderDrawColor(m_renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
}

void AppWindow::handleEvent() {
  if (m_mode == NORMAL) {
    eHandler = m_nHandler;
  } else if (m_mode == INSERT) {
    eHandler = m_iHandler;
  }
  eHandler->handle(&m_event, &lines, m_current_line, &m_mode, &cursor);
}

void AppWindow::readFile(std::string) {}
