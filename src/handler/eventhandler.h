#pragma once
#include <SDL2/SDL_events.h>
#include<string>
#include <vector>
#include"../util/models.h"
#include "../render/line.h"
#include "../render/cursor.h"

class EventHandler{
public:
  virtual void handle(SDL_Event* e,std::vector<Line>* lines, Line* line, MODE*, Cursor*)=0;
  void toggleCaps();
  bool isCapsOn();
  virtual ~EventHandler() = default;
  EventHandler();
private:
  bool caps_on = false;
  bool clear;
};
