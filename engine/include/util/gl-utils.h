#ifndef OPENGLFOO_GL_UTILS_H
#define OPENGLFOO_GL_UTILS_H

#include "../log/log-utils.h"
#include <GL/glew.h>

void printGLInfo();

#define GL_CHECK_ERROR(op) checkGLError(op, __FILE__, __LINE__)

void checkGLError(const char *op, const char * file, int line);

#endif //OPENGLFOO_GL_UTILS_H
