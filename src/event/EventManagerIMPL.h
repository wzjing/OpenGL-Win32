//
// Created by android1 on 2019/3/7.
//

#ifndef OPENGLFOO_EVENTMANAGERIMPL_H
#define OPENGLFOO_EVENTMANAGERIMPL_H

#include "EventManager.h"

class EventManagerIMPL : public EventManager {
private:
  static bool eventReady;
public:

  static EventManager* GetInstance();

  EventManagerIMPL();

  ~EventManagerIMPL();

  static void init();

  static void reset();

  bool onKey(int keyCode, int action) override;

  bool onCursor(int x, int y) override;
};


#endif //OPENGLFOO_EVENTMANAGERIMPL_H
