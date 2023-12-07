#include "AppWindow.h"
#include "TextRenderer.h"
#include "handler/InsertModeHandler.h"
#include "handler/NormalModeHandler.h"
#include "util/models.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <spdlog/spdlog.h>
#include <string>

AppWindow::AppWindow(std::string title, int x, int y, int height, int width)
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
}

AppWindow::~AppWindow() {
  SDL_Quit();
  m_window = nullptr;
  m_renderer = nullptr;
  m_font = nullptr;
}

void AppWindow::eventLoop() {

  SDL_Color Green = {255, 0, 0, 0};

  std::string font =
      "/home/chetan/.fonts/Iosevka Term Nerd Font Complete Mono Italic.ttf";
  textRenderer.setFont(font.c_str(), 18);
  m_bufferedText = "";
  while (!quit) {
    handleEvent();
    textRenderer.render_text(m_window, m_renderer, m_bufferedText, Green);
  }
}

void AppWindow::handleEvent() {
  SDL_Event e;
  if (m_mode == NORMAL) {
    eHandler = new NormalModeHandler();
  } else if (m_mode == INSERT) {
    eHandler = new InsertModeHandler();
  }
  SPDLOG_WARN("Current Mode is {}", m_mode);
  SPDLOG_WARN("Current Text is {}", m_bufferedText);
  eHandler->handle(e, m_bufferedText, &quit, &m_mode);
}
void AppWindow::readFile(std::string) {}
