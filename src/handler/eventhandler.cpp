#include "eventhandler.h"

void EventHandler::toggleCaps(){
  caps_on = !caps_on;
}

bool EventHandler::isCapsOn(){
  return caps_on;
}

void EventHandler::clearRenderer(bool value){
  this->clear = value;
}

bool EventHandler::shouldClearRender(){
  return clear;
}
