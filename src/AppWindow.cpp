#include "AppWindow.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_filesystem.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <spdlog/spdlog.h>

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
  m_surface = SDL_GetWindowSurface(m_window);
  if (m_surface == nullptr) {
    SPDLOG_ERROR("Unable to get window surface! Error: {}\n", SDL_GetError());
    exit(1);
  }
  std::string font_path = "/usr/share/fonts/truetype/ubuntu/Ubuntu-C.ttf";
  m_font = TTF_OpenFont(font_path.c_str(), 24);
  if (m_font == nullptr) {
    SPDLOG_ERROR("Unable to open font! Error: {}\n", SDL_GetError());
    SDL_Quit();
    exit(1);
  }

  SDL_Color White = {255, 255, 255, 0};

  m_surface = TTF_RenderText_Solid(m_font, "put your text here", White);
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

  Message_rect.x = 0;   // controls the rect's x coordinate
  Message_rect.y = 0;   // controls the rect's y coordinte
  Message_rect.w = 100; // controls the width of the rect
  Message_rect.h = 100; // controls the height of the rect

  SDL_RenderCopy(m_renderer, m_texture, NULL, &Message_rect);
}

AppWindow::~AppWindow() {
  SDL_FreeSurface(m_surface);
  m_surface = nullptr;
  SDL_Quit();
}

void AppWindow::writeText() {
  /*std::string font_path = std::string(SDL_GetBasePath()).append("font.ttf");*/
  SDL_SetRenderDrawColor(m_renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(m_renderer);

  SDL_RenderCopy(m_renderer, m_texture, NULL, &Message_rect);
  SDL_RenderPresent(m_renderer);
}

void AppWindow::eventLoop() {
  SDL_Event e;
  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT)
        quit = true;
      else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
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
        case SDLK_q:
          quit = true;
          break;
        }
      }
    }
    writeText();
  }
}

void AppWindow::setSurface(SDL_Surface *surface) { this->m_surface = surface; }
