#pragma once
#include <SDL2/SDL_events.h>
#include<string>
#include"../util/models.h"

class EventHandler{
public:
  virtual void handle(SDL_Event e, std::string&, bool*, MODE*)=0;
};
