#include "NormalModeHandler.h"
#include <iostream>
#include <spdlog/spdlog.h>

void NormalModeHandler::handle(SDL_Event *e, Line *, bool *quit, MODE *mode,
                               Cursor *cursor) {
  if (SDL_PollEvent(e) != 0) {
    if ((*e).type == SDL_QUIT)
      *quit = true;
    else if ((*e).type == SDL_KEYDOWN) {
      SDL_Keysym keysym = (*e).key.keysym;
      switch (keysym.sym) {
      case SDLK_UP:
      case SDLK_k:
        cursor->moveup();
        break;
      case SDLK_DOWN:
      case SDLK_j:
        cursor->movedown();
        break;
      case SDLK_RIGHT:
      case SDLK_l:
        cursor->moveright();
        break;
      case SDLK_LEFT:
      case SDLK_h:
        cursor->moveleft();
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
      case SDLK_CAPSLOCK:
        toggleCaps();
        break;
      default:
        SPDLOG_WARN("Event {} not handle", keysym.sym);
      }
    }
  }
}
