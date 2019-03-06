//
// Created by android1 on 2019/3/6.
//

#ifndef OPENGLFOO_EVENTMANAGER_H
#define OPENGLFOO_EVENTMANAGER_H


class EventManager {
public:
  virtual bool onKey(int keyCode, int action) = 0;
  virtual bool onCursor(int x, int y) = 0;
};


#endif //OPENGLFOO_EVENTMANAGER_H
