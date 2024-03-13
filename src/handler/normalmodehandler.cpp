#include "normalmodehandler.h"
#include <iostream>
#include <spdlog/spdlog.h>

void NormalModeHandler::handle(SDL_Event *e, std::vector<Line> *, Line *,
                               MODE *mode, Cursor *) {
  if ((*e).type == SDL_KEYDOWN) {
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
