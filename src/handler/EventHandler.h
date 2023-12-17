#pragma once
#include <SDL2/SDL_events.h>
#include<string>
#include"../util/models.h"
#include "../render/Line.h"
#include "../render/cursor.h"

class EventHandler{
public:
  virtual void handle(SDL_Event* e, Line* line,bool*, MODE*, Cursor*)=0;
  void toggleCaps();
  bool isCapsOn();
  bool shouldClearRender();
  void clearRenderer(bool value);
private:
  bool caps_on;
  bool clear;
};
