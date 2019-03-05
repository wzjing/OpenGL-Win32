#include "gl-utils.h"

void printGLInfo() {
  printf("OpenGL Information ->\n"
         "\tRenderer       : %s\n"
         "\tOpenGL Version : %s\n"
         "\tShader Version : %s\n",
         glGetString(GL_RENDERER),
         glGetString(GL_VERSION),
         glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void checkGLError(const char *op, const char * filename, int line) {
    for (GLint error = glGetError(); error ; error = glGetError()) {
        const char * detail;
        switch (error) {
            case GL_INVALID_ENUM:
                detail =  "Invalid argument enum";
                break;
            case GL_INVALID_VALUE:
                detail =  "Invalid argument value";
                break;
            case GL_INVALID_OPERATION:
                detail = "Invalid operation";
                break;
            case GL_OUT_OF_MEMORY:
                detail = "Out Of Memory";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                detail = "Frame Buffer Error";
                break;
            default:
                detail = "Unknown Error";
                break;
        }
        LOGD("OpenGL Error ->\n"
             "\tmessage   : %s\n"
             "\toperation : %s\n"
             "\tposition  : %s line %d\n", detail, op, filename, line);
    }
}
