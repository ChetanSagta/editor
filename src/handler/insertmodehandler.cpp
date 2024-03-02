#include "insertmodehandler.h"
#include "../util/string_helper.h"
#include <SDL2/SDL_keycode.h>
#include <fmt/core.h>
#include <spdlog/spdlog.h>

void InsertModeHandler::handle(SDL_Event *e, Line *line, bool *quit, MODE *mode,
                               Cursor *cursor) {
  if ((*e).type == SDL_QUIT)
    *quit = true;
  else if ((*e).type == SDL_KEYDOWN) {
    SDL_Keysym keysym = (*e).key.keysym;
    switch (keysym.sym) {
    case SDLK_ESCAPE:
      *mode = NORMAL;
      break;
    case SDLK_UP:
      cursor->moveup();
      break;
    case SDLK_DOWN:
      cursor->movedown();
      break;
    case SDLK_RIGHT:
      cursor->moveright();
      break;
    case SDLK_LEFT:
      cursor->moveleft();
      break;
    case SDLK_RETURN:
      /*bufferedText.append("\n");*/
      // TODO: add new line here
      break;
    case SDLK_CAPSLOCK:
      SPDLOG_INFO("CapsLock is {}", isCapsOn());
      toggleCaps();
      break;
    case SDLK_LSHIFT:
    case SDLK_RSHIFT:
      toggleCaps();
      break;
    case SDLK_SPACE:
      line->addCharsAtEnd(" ");
      break;
    case SDLK_BACKSPACE:
      line->removeCharAtEnd();
      clearRenderer(true);
      break;
    default:
      std::string keyname = SDL_GetKeyName(keysym.sym);
      if (isCapsOn()) {
        line->addCharsAtEnd(to_upper(keyname));
      } else {
        line->addCharsAtEnd(to_lower(keyname));
      }
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

void InsertModeHandler::toggleCaps() { caps_on = !caps_on; }

bool InsertModeHandler::isCapsOn() { return caps_on; }
