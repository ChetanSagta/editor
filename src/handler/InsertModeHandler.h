#pragma once

#include "EventHandler.h"
class InsertModeHandler: public EventHandler{
  public:
  void handle(SDL_Event* e, Line* line, bool*, MODE*, Cursor*) override;
};
