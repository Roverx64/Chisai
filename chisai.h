#pragma once

#include <stdint.h>
#include <stdbool.h>

#define LOG_GENERAL 0,__FUNCTION__,__LINE__
#define LOG_INFO 1,__FUNCTION__,__LINE__
#define LOG_WARN 2,__FUNCTION__,__LINE__
#define LOG_ERROR 3,__FUNCTION__,__LINE__
#define LOG_FATAL 4,__FUNCTION__,__LINE__

extern void setLoggingFormat(char *format);
extern int enableFileLogging(const char *path, bool create);
extern void setLogLevelStrings(char *general, char *info, char *warn, char *error, char *fatal);
extern void writeLog(int level, const char *func, int line, const char *str, ...);
extern void closeLog();
