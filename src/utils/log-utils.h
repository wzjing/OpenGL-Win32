#ifndef OPENGLFOO_LOG_UTILS_H
#define OPENGLFOO_LOG_UTILS_H

#include <cstdio>
#include <cerrno>

#define LOG(format, ...) printf(format, ## __VA_ARGS__)
#ifdef DEBUG
#define LOGD(format, ...) printf(format, ## __VA_ARGS__)
#elif
#define LOGD(format, ...)
#endif
#define LOGE(format, ...) fprintf(stderr, format, ## __VA_ARGS__)

#endif //OPENGLFOO_LOG_UTILS_H
