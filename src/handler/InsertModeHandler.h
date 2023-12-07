#pragma once

#include "EventHandler.h"
class InsertModeHandler: public EventHandler{
  public:
  void handle(SDL_Event e, std::string&, bool*, MODE*) override;
};
