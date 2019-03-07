//
// Created by wzjing on 2019/2/20.
//

#include <stdexcept>
#include "GameEgine.h"
#include "utils/gl-utils.h"
#include "utils/log-utils.h"

void glInit();

void glResize(int width, int height);

void glStep();

void event_callback(GLFWwindow *window, int key, int scanCode, int action, int mods) {
  GameEngine::eventManager->onKey(key, action);
}

GameEngine::GameEngine(const char *name, bool fullScreen, int minWidth, int minHeight) :
        name(name),
        fullScreen(fullScreen), minWidth(minWidth), minHeight(minHeight) {

}

GameEngine::~GameEngine() {
  glfwSetErrorCallback([](int error, const char *description) -> void {
    LOGE("GameEngine(ERROR): glfw error %d, %s\n", error, description);
  });
  if (!glfwInit()) {
    LOGE("GameEngine(ERROR): unable to init glfw\n");
    throw std::runtime_error("unable to init glfw");
  }

  window = glfwCreateWindow(minWidth, minHeight, name, nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    LOGE("GameEngine(ERROR): unable to create window\n");
    throw std::runtime_error("unable to create window");
  }

  if (glewInit() != GLEW_OK) {
    LOGE("GameEngine(Error): unable to init glew\n");
    throw std::runtime_error("unable to init glew");
  }

  eventManager = new EventManagerIMPL();

  glfwSetKeyCallback(window, event_callback);

  glInit();

}

void GameEngine::start() {
  while (window != nullptr && !glfwWindowShouldClose(window)) {
    glStep();

    glfwSwapBuffers(window);

    glfwPollEvents();
  }
}

void GameEngine::pause() {

}

void GameEngine::destroy() {
  if (window != nullptr) {
    glfwDestroyWindow(window);
  }
  glfwTerminate();
}
