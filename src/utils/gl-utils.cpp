#include "gl-utils.h"


void checkGlError(const char* op) {
    for (GLint error = glGetError(); error ; error = glGetError()) {
        switch (error) {
            case GL_INVALID_ENUM:
                LOG("Operation: %s Error: 0x%x(%s)\n", op, error, "Invalid argument enum");
                break;
            case GL_INVALID_VALUE:
                LOG("Operation: %s Error: 0x%x(%s)\n", op, error, "Invalid argument value");
                break;
            case GL_INVALID_OPERATION:
                LOG("Operation: %s Error: 0x%x(%s)\n", op, error, "Invalid operation");
                break;
            case GL_OUT_OF_MEMORY:
                LOG("Operation: %s Error: 0x%x(%s)\n", op, error, "Out Of Memory");
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                LOG("Operation: %s Error: 0x%x(%s)\n", op, error, "Frame Buffer Error");
                break;
            default:
                LOG("Operation: %s Error: 0x%x(%s)\n", op, error, "Unknown Error");
                break;
        }
    }
}