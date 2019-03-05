#ifndef OPENGLFOO_GL_UTILS_H
#define OPENGLFOO_GL_UTILS_H

#include <GL/glew.h>
#include "log-utils.h"

void printGLInfo();

#define GL_CHECK_ERROR(op) checkGLError(op, __FILE__, __LINE__)

void checkGLError(const char *op, const char * file, int line);

#endif //OPENGLFOO_GL_UTILS_H
