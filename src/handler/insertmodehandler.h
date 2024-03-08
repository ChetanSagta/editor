#pragma once

#include "eventhandler.h"
class InsertModeHandler: public EventHandler{
  public:
  void handle(SDL_Event* e,std::vector<Line>* lines, Line* line, bool*, MODE*, Cursor*) override;
  void toggleCaps();
  bool isCapsOn();
  private:
  bool caps_on;
};
