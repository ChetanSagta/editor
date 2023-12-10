#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include "AppWindow.h"

int main(int, char *[]) {

  AppWindow *mainWindow = new AppWindow("Text Editor", 0, 0,800, 600);
  mainWindow->eventLoop();
  return 0;
}
