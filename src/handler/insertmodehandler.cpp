#include "insertmodehandler.h"
#include "../util/string_helper.h"
#include <SDL2/SDL_keycode.h>
#include <spdlog/spdlog.h>

void InsertModeHandler::handle(SDL_Event *e, std::vector<Line> *lines,
                               Line *line,MODE *mode,
                               Cursor *cursor) {
  if ((*e).type == SDL_KEYDOWN) {
    SDL_Keysym keysym = (*e).key.keysym;
    switch (keysym.sym) {
    case SDLK_ESCAPE:
      *mode = NORMAL;
      break;
    case SDLK_RETURN:
      lines->push_back(*line);
      line->setLineNumber(line->getLineNumber()+1);
      line->setLastLineHeight(line->getLineHeight());
      line->setText("");
      cursor->moveToNextLine();
      break;
    case SDLK_CAPSLOCK:
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
      cursor->moveleft();
      break;
    default:
      std::string keyname = SDL_GetKeyName(keysym.sym);
      if (isCapsOn()) {
        line->addCharsAtEnd(to_upper(keyname));
      } else {
        line->addCharsAtEnd(to_lower(keyname));
      }
      cursor->moveright();
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
