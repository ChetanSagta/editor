#include "NormalModeHandler.h"
#include<iostream>
#include<spdlog/spdlog.h>

void NormalModeHandler::handle(SDL_Event e, std::string&, bool* quit, MODE* mode) {
  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT)
      *quit = true;
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
        if (*mode == INSERT) {
          *mode = NORMAL;
          break;
        }
        break;
      case SDLK_i:
          *mode = INSERT;
          break;
      case SDLK_q:
          *quit = true;
          break;
      default:
        SPDLOG_WARN("Event {} not handle", keysym.sym);
      }
    }
  }
}
