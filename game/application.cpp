//#define GLEW_STATIC

#include <model/component/Shader.h>
#include <log/log-utils.h>
#include <util/asset_loader.h>
#include <util/gl-utils.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <pthread.h>
#include <stdexcept>
#include <string>

const int defaultWidth = 640;
const int defaultHeight = 480;

int currentWidth = 0;
int currentHeight = 0;
float verticalRotation = 0.0f;
float horizontalRotation = 90.0f;
int radius = 5;
int step = 3;

float vertices[] = {
    -1, -1, 1, -1, 1, 1, -1, 1,

};
GLuint indices[] = {0, 1, 2, 2, 3, 0};

float cubeVertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.5f,  -0.5f, -0.5f,
    0.0f,  0.0f,  -1.0f, 0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f,
    0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, -0.5f, 0.5f,  -0.5f,
    0.0f,  0.0f,  -1.0f, -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f,

    -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,
    0.0f,  0.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  -0.5f, 0.5f,  0.5f,
    0.0f,  0.0f,  1.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,

    -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  -0.5f, 0.5f,  -0.5f,
    -1.0f, 0.0f,  0.0f,  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  -0.5f, -0.5f, 0.5f,
    -1.0f, 0.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,

    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.5f,  0.5f,  -0.5f,
    1.0f,  0.0f,  0.0f,  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,
    0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.5f,  -0.5f, 0.5f,
    1.0f,  0.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f, -0.5f,
    0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,
    0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  -0.5f, -0.5f, 0.5f,
    0.0f,  -1.0f, 0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,

    -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  -0.5f,
    0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,
    0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f};

GLuint vboId;
GLuint eboId;
GLuint vaoId;

Shader *shader;

float start;

float getMilliSecs() {
  auto now = std::chrono::high_resolution_clock::now();
  long nanoSec = now.time_since_epoch().count() / 1000000;
  float sec = nanoSec / 1000.0f;
  return sec;
}
#define PI 3.14159265f
void glInit();
void glResize(int width, int height);
void glStep();
void rotate(glm::vec2 rotation);

float getX() { return cos(horizontalRotation / 180 * PI) * radius; }

float getY() {
  return sqrt(radius - cos(verticalRotation / 180 * PI) * radius);
}

float getZ() {
  return sqrt(cos(verticalRotation / 180 * PI) * radius -
              pow(cos(horizontalRotation / 180 * PI) * radius, 2));
}

void glInit() {
  printGLInfo();
  start = getMilliSecs();
  shader = new Shader(load_text("/shader/vertex_shader.glsl"),
                      load_text("/shader/fragment_color.glsl"));

  glResize(defaultWidth, defaultHeight);
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_DEPTH);

  // VBO: Vertex Buffer Object
  glGenBuffers(1, &vboId);
  glBindBuffer(GL_ARRAY_BUFFER, vboId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // EBO: Element Buffer Object
  glGenBuffers(1, &eboId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);
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
  glm::mat4 Projection = glm::perspective(
      glm::radians(30.0f), (float)currentWidth / currentHeight, 0.1f, 100.0f);
  //  auto m_position = glm::vec3(getX(), getY(), getZ());
  //  auto m_direction = glm::vec3(0, 0, 0);
  auto camera_pos = glm::vec3(getX(), getY(), getZ());
  auto object_pos = glm::vec3(0, 0, 3);
  auto world_up = glm::vec3(0, 1, 0);
  glm::mat4 View = glm::lookAt(camera_pos + object_pos, object_pos, world_up);
  glm::mat4 Model = glm::mat4(1.0f);

  //  float degree = 360 * sin((float) clock() / (10 * CLOCKS_PER_SEC));
  //  glm::mat4 rotatedView = glm::rotate(View, degree, glm::vec3(0, 1, 0));

  glm::mat4 mvp = Projection * View * Model;

  shader->use();
  shader->setUniform("iGlobalTime", getMilliSecs());
  shader->setUniform(
      "iResolution", 2,
      std::array<float, 2>{(float)currentWidth, (float)currentHeight}.data());
  shader->setUniform("mvp", 4, 4, &mvp[0][0]);

  glBindVertexArray(vaoId);
  glBindBuffer(GL_ARRAY_BUFFER, vboId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);

  GL_CHECK_ERROR("bind buffers");
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
  GL_CHECK_ERROR("draw element");

  glBindVertexArray(0);

  //  shader->unUse();
}

static void error_callback(int error, const char *description) {
  fprintf(stderr, "Error: (%d)%s\n", error, description);
}
static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  LOGD("Key: %d, %d\n", key, action);
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);

  if (action == GLFW_REPEAT || action == GLFW_PRESS) {
    switch (key) {
    case GLFW_KEY_LEFT:
      rotate(glm::vec2(0 - step, 0));
      break;
    case GLFW_KEY_RIGHT:
      rotate(glm::vec2(step, 0));
      break;
    case GLFW_KEY_DOWN:
      rotate(glm::vec2(0, step));
      break;
    case GLFW_KEY_UP:
      rotate(glm::vec2(0, 0 - step));
      break;
    default:
      break;
    }
  }

  if (action == GLFW_PRESS && key == GLFW_KEY_SPACE) {
    horizontalRotation = 90;
    verticalRotation = 0;
  }
}
static void size_callback(GLFWwindow *window, int width, int height) {
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
  window =
      glfwCreateWindow(defaultWidth, defaultHeight, "OpenGL", nullptr, nullptr);
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

// rotation like star trek
void rotate(glm::vec2 rotation) {
  horizontalRotation += rotation.x;
  verticalRotation += rotation.y;
  LOGD("rotate : [%f˚, %f˚] -> (%f, %f, %f), distance = %f\n", verticalRotation,
       horizontalRotation, getX(), getY(), getZ(),
       sqrt(pow(getX(), 2) + pow(getY(), 2) + pow(getZ(), 2)));
}