//
// Created by wzjing on 2019/2/20.
//

#ifndef OPENGL_WIN32_APPLICATION_H
#define OPENGL_WIN32_APPLICATION_H

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <GL/eglew.h>
#include <pthread.h>
#include "event/EventManager.h"

class GameEngine {
private:
  GLFWwindow *window;
  EventManager* eventManager;
  const char *name;
  bool fullScreen;
  int minWidth;
  int minHeight;
public:
  GameEngine(const char *name, bool fullScreen, int minWidth, int minHeight);

  ~GameEngine();

  void start();

  void pause();

  void destroy();
};


#endif //OPENGL_WIN32_APPLICATION_H
