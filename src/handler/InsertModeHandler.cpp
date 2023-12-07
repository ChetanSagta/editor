#include "InsertModeHandler.h"

void InsertModeHandler::handle(SDL_Event e, std::string& bufferedText, bool* quit, MODE* mode) {
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
      default:
        bufferedText.append(SDL_GetKeyName(keysym.sym));
        break;
      }
    }
  }
}
