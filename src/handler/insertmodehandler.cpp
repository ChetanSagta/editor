#include "insertmodehandler.h"
#include <SDL2/SDL_keycode.h>
#include <spdlog/spdlog.h>

void InsertModeHandler::handle(SDL_Event* e, Line *line, bool *quit,
                               MODE *mode,Cursor* cursor) {
  if(SDL_PollEvent(e) != 0) {
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
      case SDLK_i:
        line->addChars("i");
        break;
      case SDLK_q:
        line->addChars("q");
        break;
      case SDLK_RETURN:
        /*bufferedText.append("\n");*/
        // TODO: add new line here
        break;
      case SDLK_CAPSLOCK:
        toggleCaps();
        break;
      case SDLK_SPACE:
        line->addChars(" ");
        break;
      case SDLK_BACKSPACE:
        line->removeChar();
        clearRenderer(true);
        break;
      default:
        const char *ch = SDL_GetKeyName(keysym.sym);
        /*if (!isCapsOn()) {*/
        /*  const char chr = std::tolower(static_cast<unsigned char>(*ch));*/
        /*  bufferedText.append(&chr);*/
        /*} else*/
        line->addChars(ch);
      }
    }
  }
}
