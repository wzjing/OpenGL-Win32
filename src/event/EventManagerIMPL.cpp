//
// Created by android1 on 2019/3/7.
//

#include "EventManagerIMPL.h"

bool EventManagerIMPL::onKey(int keyCode, int action) {
  return false;
}

bool EventManagerIMPL::onCursor(int x, int y) {
  return false;
}

EventManagerIMPL::EventManagerIMPL(): EventManager() {

}

EventManagerIMPL::~EventManagerIMPL() {

}

void EventManagerIMPL::init() {
  eventReady = true;
}

void EventManagerIMPL::reset() {
  eventReady = false;
}
