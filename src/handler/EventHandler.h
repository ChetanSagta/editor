#pragma once
#include <SDL2/SDL_events.h>
#include<string>
#include"../util/models.h"
#include "../util/helper.h"

class EventHandler{
public:
  virtual void handle(SDL_Event e, std::string&, bool*, MODE*)=0;
  void toggleCaps();
  bool isCapsOn();
  Helper helper;
private:
  bool caps_on;
};
