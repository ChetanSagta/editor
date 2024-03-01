#include "normalmodehandler.h"
#include <iostream>
#include <spdlog/spdlog.h>

void NormalModeHandler::handle(SDL_Event *e, Line *, bool *quit, MODE *mode,
                               Cursor *) {
  if (SDL_PollEvent(e) != 0) {
    if ((*e).type == SDL_QUIT)
      *quit = true;
    else if ((*e).type == SDL_KEYDOWN) {
      SDL_Keysym keysym = (*e).key.keysym;
      switch (keysym.sym) {
      case SDLK_ESCAPE:
        if (*mode == INSERT) {
          *mode = NORMAL;
        }
        break;
      case SDLK_CAPSLOCK:
        toggleCaps();
        break;
      case SDLK_LSHIFT:
      case SDLK_RSHIFT:
        toggleCaps();
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
    } else if ((*e).type == SDL_KEYUP) {
      SDL_Keysym keysym = (*e).key.keysym;
      switch (keysym.sym) {
      case SDLK_LSHIFT:
      case SDLK_RSHIFT:
        toggleCaps();
        break;
      }
    }
  }
}
