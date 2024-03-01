#include "eventhandler.h"
#include <iostream>
#include <spdlog/spdlog.h>

EventHandler::EventHandler(){
  EventHandler::caps_on = false;
}

void EventHandler::toggleCaps(){
  EventHandler::caps_on = !EventHandler::caps_on;
}

bool EventHandler::isCapsOn(){
  return EventHandler::caps_on;
}

void EventHandler::clearRenderer(bool value){
  clear = value;
}

bool EventHandler::shouldClearRender(){
  return clear;
}
