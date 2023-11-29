#include "AppWindow.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_filesystem.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <spdlog/spdlog.h>
#include <string>

AppWindow::AppWindow(std::string title, int x, int y, int height, int width) {
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
  std::string font_path = "/usr/share/fonts/truetype/ubuntu/Ubuntu-C.ttf";
  m_font = TTF_OpenFont(font_path.c_str(), 24);
  if (m_font == nullptr) {
    SPDLOG_ERROR("Unable to open font! Error: {}\n", SDL_GetError());
    SDL_Quit();
    exit(1);
  }
}

AppWindow::~AppWindow() {
  SDL_FreeSurface(m_surface);
  m_surface = nullptr;
  SDL_Quit();
}

void AppWindow::writeText() {
  SDL_Color Green = {0, 255, 0, 0};

  /*std::string text =*/
  /*    "This is a very long text created to test the width of the message box";*/
  m_surface = TTF_RenderText_Solid(m_font, m_bufferedText.c_str(), Green);
  if (m_surface == nullptr) {
    SPDLOG_ERROR("Unable to create render text solid! Error: {}\n",
                 SDL_GetError());
    SDL_Quit();
    exit(1);
  }
  m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
  SDL_FreeSurface(m_surface);
  if (m_texture == nullptr) {
    SPDLOG_ERROR("Unable to create render text from surface ! Error: {}\n",
                 SDL_GetError());
    SDL_Quit();
    exit(1);
  }

  SDL_Rect Message_rect;
  Message_rect.x = 0;            // controls the rect's x coordinate
  Message_rect.y = 0;            // controls the rect's y coordinte
  Message_rect.w = m_surface->w; // controls the width of the rect
  Message_rect.h = m_surface->h; // controls the height of the rect

  SDL_RenderClear(m_renderer);
  SDL_RenderCopy(m_renderer, m_texture, NULL, &Message_rect);
  SDL_SetRenderDrawColor(m_renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);
  SDL_RenderPresent(m_renderer);
}

void AppWindow::eventLoop() {
  SDL_Event e;
  while (!quit) {
    writeText();
    handleEvent(e);
  }
}

void AppWindow::setSurface(SDL_Surface *surface) { this->m_surface = surface; }

void AppWindow::handleEvent(SDL_Event e) {
  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT)
      quit = true;
    else if (e.type == SDL_KEYDOWN) {
      SDL_Keysym keysym = e.key.keysym;
      switch (keysym.sym) {
      case SDLK_UP:
        std::cout << "UP" << std::endl;
        break;
      case SDLK_DOWN:
        std::cout << "DOWN" << std::endl;
        break;
      case SDLK_RIGHT:
        std::cout << "RIGHT" << std::endl;
        break;
      case SDLK_LEFT:
        std::cout << "LEFT" << std::endl;
        break;
      case SDLK_ESCAPE:
        if (m_mode == INSERT) {
          m_mode = NORMAL;
          break;
        }
        break;
      case SDLK_i:
        if (m_mode == NORMAL) {
          m_mode = INSERT;
          break;
        } else if (m_mode == INSERT) {
          m_bufferedText.append("i");
          break;
        }
        break;
      case SDLK_q:
        if (m_mode == NORMAL) {
          quit = true;
          break;
        }
        m_bufferedText.append("q");
        break;
      default:
        m_bufferedText.append(SDL_GetKeyName(keysym.sym));
        break;
      }
    }
  }
}

void AppWindow::readFile(std::string) {}
