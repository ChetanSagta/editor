#pragma once

#include<SDL2/SDL_events.h>
#include "EventHandler.h"
class NormalModeHandler: public EventHandler{
  public:
  void handle(SDL_Event e, std::string&, bool*, MODE*) override;
};
