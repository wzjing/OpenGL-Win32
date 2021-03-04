//
// Created by Infinity on 2019-03-13.
//

#ifndef OPENGLFOO_EVENTLISTENER_H
#define OPENGLFOO_EVENTLISTENER_H

class EventListener {
 public:
  virtual bool onKey(int keyCode, int action) = 0;
  virtual bool onTouch()
};

#endif //OPENGLFOO_EVENTLISTENER_H
