#ifndef OPENGLFOO_LOG_UTILS_H
#define OPENGLFOO_LOG_UTILS_H

#include <cstdio>

#define LOG(format, ...) printf(format, ## __VA_ARGS__)
#ifdef DEBUG
#define LOGD(format, ...) printf(format, ## __VA_ARGS__)
#elif
#define LOGD(format, ...)
#endif

#endif //OPENGLFOO_LOG_UTILS_H
