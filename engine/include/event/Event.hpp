//
// Created by Infinity on 2019-03-13.
//

#ifndef OPENGLFOO_EVENT_HPP
#define OPENGLFOO_EVENT_HPP

#define ACTION_TOUCH_DOWN 0x1;
#define ACTION_TOUCH_UP 0x2;
#define ACTION_MOVE 0x3

#define POINTER_INDEX_MASK 0xFF00


class Event {
 public:
  int x;
  int y;
  int action;
  int getPointerIndex() {
    return (action&POINTER_INDEX_MASK)>>16
  }
};

#endif //OPENGLFOO_EVENT_HPP
