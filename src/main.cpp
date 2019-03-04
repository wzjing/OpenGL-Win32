//#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <chrono>
#include <stdexcept>
#include "utils/asset_loader.h"
#include "utils/log-utils.h"
#include "Shader.h"
#include "utils/gl-utils.h"

const int width = 640;
const int height = 480;

float resolution[] = {float(width), float(height)};

float vertices[] = {
        -1, -1,
        1, -1,
        1, 1,
        -1, 1
};
GLuint indices[] = {
        0, 1, 2,
        2, 3, 0
};

GLuint vboId;
GLuint eboId;
GLuint vaoId;

Shader *shader;

long long int start;

float getSeconds() {
  long long int now = std::chrono::system_clock::now().time_since_epoch().count();
  long nanoSec = (now - start)/1000;
  float sec = nanoSec/10000.0f;
  LOGD("Seconds: %.03f\n", sec);
  return sec;
}

void glInit() {
  printf("OpenGL Version: %s\n"
         "Shader Version: %s\n",
         glGetString(GL_VERSION),
         glGetString(GL_SHADING_LANGUAGE_VERSION));
  start = std::chrono::system_clock::now().time_since_epoch().count();
  glViewport(0, 0, width, height);
  shader = new Shader(load_text("/shader/vertex_shader.glsl"), load_text("/shader/fragment_sea.glsl"));


  // VBO: Vertex Buffer Object
  glGenBuffers(1, &vboId);
  glBindBuffer(GL_ARRAY_BUFFER, vboId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  //EBO: Element Buffer Object
  glGenBuffers(1, &eboId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // VAO: Vertex Array Object
  glGenVertexArrays(1, &vaoId);
  glBindVertexArray(vaoId);
  glBindBuffer(GL_ARRAY_BUFFER, vaoId);
  shader->setAttribute("vertexPosition", 2, 2 * sizeof(float));
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);

  glBindVertexArray(0);

}

void glStep() {
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(1.0, 1.0, 1.0, 1.0);

  shader->use();
  shader->setUniform("iGlobalTime", getSeconds());
  shader->setUniform("iResolution", 2, resolution);

  glBindVertexArray(vaoId);
  glBindBuffer(GL_ARRAY_BUFFER, vboId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);

  checkGlError("bind buffers");
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

  glBindVertexArray(0);

//  shader->unUse();
}

int main() {
  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(width, height, "OpenGL", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  GLenum ret = glewInit();
  if (ret != GLEW_OK) {
    LOG("GLEW initial error: %s", glewGetErrorString(ret));
    glfwTerminate();
    return -2;
  }

  glInit();

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glStep();

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}