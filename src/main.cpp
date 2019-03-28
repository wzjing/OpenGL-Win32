//#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string>
#include <chrono>
#include <stdexcept>
#include <pthread.h>
#include "utils/asset_loader.h"
#include "utils/log-utils.h"
#include "model/component/Shader.h"
#include "utils/gl-utils.h"

const int defaultWidth = 640;
const int defaultHeight = 480;

int currentWidth = 0;
int currentHeight = 0;

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

float start;

float getSeconds() {
  auto now = std::chrono::high_resolution_clock::now();
  long nanoSec = now.time_since_epoch().count() / 1000000;
  float sec = nanoSec / 1000.0f;
  return sec;
}

void glInit();
void glResize(int width, int height);
void glStep();

void glInit() {
  printGLInfo();
  start = getSeconds();
  shader = new Shader(load_text("/shader/vertex_shader.glsl"), load_text("/shader/fragment_sea.glsl"));

  glResize(defaultWidth, defaultHeight);
  glEnable(GL_MULTISAMPLE);


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

void glResize(int width, int height) {
  glViewport(0, 0, width, height);
  currentWidth = width;
  currentHeight = height;
}

void glStep() {
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(1.0, 1.0, 1.0, 1.0);


  // Shader: projectionMatrix;
  glm::mat4 Projection = glm::perspective(glm::radians(30.0f), (float)currentWidth / currentHeight, 0.1f,
                                          100.0f);
  glm::mat4 View = glm::lookAt(
          glm::vec3(4, 3, 3),
          glm::vec3(0, 0, 0),
          glm::vec3(0, 1, 0)
  );
  glm::mat4 Model = glm::mat4(1.0f);

//  float degree = 360 * sin((float) clock() / (10 * CLOCKS_PER_SEC));
//  glm::mat4 rotatedView = glm::rotate(View, degree, glm::vec3(0, 1, 0));

  glm::mat4 mvp = Projection * View * Model;

  shader->use();
  shader->setUniform("iGlobalTime", getSeconds());
  shader->setUniform("iResolution", 2, std::array<float, 2>{(float) currentWidth, (float) currentHeight}.data());
  shader->setUniform("mvp", 4, 4, &mvp[0][0]);

  glBindVertexArray(vaoId);
  glBindBuffer(GL_ARRAY_BUFFER, vboId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);

  GL_CHECK_ERROR("bind buffers");
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

  glBindVertexArray(0);

//  shader->unUse();
}

static void error_callback(int error, const char* description)
{
  fprintf(stderr, "Error: (%d)%s\n", error, description);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  else{
    LOGD("Key: %d\n", key);
  }
}
static void size_callback(GLFWwindow* window, int width, int height) {
  glResize(width, height);
  glStep();
}

int main() {
  GLFWwindow *window;

  glfwSetErrorCallback(error_callback);

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 16);

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(defaultWidth, defaultHeight, "OpenGL", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwSetKeyCallback(window, key_callback);
  glfwSetWindowSizeCallback(window, size_callback);

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  GLenum ret = glewInit();
  if (ret != GLEW_OK) {
    LOG("GLEW initial error: %s", glewGetErrorString(ret));
    glfwTerminate();
    return -2;
  }
  GL_CHECK_ERROR("Before Init");
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

  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}