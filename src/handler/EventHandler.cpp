#include "EventHandler.h"

void EventHandler::toggleCaps(){
  caps_on = !caps_on;
}

bool EventHandler::isCapsOn(){
  return caps_on;
}
