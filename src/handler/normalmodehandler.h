#pragma once

#include<SDL2/SDL_events.h>
#include "eventhandler.h"
class NormalModeHandler: public EventHandler{
  public:
  void handle(SDL_Event* e,std::vector<Line>* lines,Line* line, bool*, MODE*, Cursor*) override;
};
