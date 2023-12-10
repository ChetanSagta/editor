#include "InsertModeHandler.h"
#include <SDL2/SDL_keycode.h>
#include <locale>

void InsertModeHandler::handle(SDL_Event e, std::string &bufferedText,
                               bool *quit, MODE *mode) {
  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT)
      *quit = true;
    else if (e.type == SDL_KEYDOWN) {
      SDL_Keysym keysym = e.key.keysym;
      switch (keysym.sym) {
      case SDLK_ESCAPE:
        *mode = NORMAL;
        break;
      case SDLK_i:
        bufferedText.append("i");
        break;
      case SDLK_q:
        bufferedText.append("q");
        break;
      case SDLK_RETURN:
        bufferedText.append("\n");
        break;
      case SDLK_CAPSLOCK:
        toggleCaps();
        break;
      case SDLK_SPACE:
        bufferedText.append(" ");
        break;
      case SDLK_BACKSPACE:
        bufferedText = helper.remove_last_char(bufferedText);
        break;
      default:
        const char *ch = SDL_GetKeyName(keysym.sym);
        /*if (!isCapsOn()) {*/
        /*  const char chr = std::tolower(static_cast<unsigned char>(*ch));*/
        /*  bufferedText.append(&chr);*/
        /*} else*/
        bufferedText.append(ch);
      }
    }
  }
}
