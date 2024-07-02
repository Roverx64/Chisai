#pragma once

#include <stdint.h>

#define CHI_OPT_FILE_OUT 1<<0
#define CHI_OPT_NO_STDOUT 1<<1

#define CHI_OPT_GET_LOG_LEVEL(l) ((l>>4)&0xFF)
#define CHI_OPT_SET_LOG_LEVEL(o,l) (o|(((uint32_t)(l&0xFF))<<4))

#define CHI_ALL 0
#define CHI_GENERAL 0
#define CHI_VERBOSE 1
#define CHI_INFO 2
#define CHI_WARN 3
#define CHI_ERROR 4
#define CHI_FATAL 5

extern void chiSetLoggingFormat(char *format);
extern int chiEnableFileLogging(const char *path, bool create);
extern void chiSetLogStrings(char *general, char *info, char *warn, char *error, char *fatal, char *verbose);
extern void chiSetLoggingLevel(uint8_t level);
extern void chiSetLogOptions(uint32_t opt);
extern void chiWriteLog_int(int level, const char *func, int line, const char *str, ...);
extern void chiCloseLog();

//NOTE: ##__VA_ARGS__ is a GCC specific workaround
//TODO: Use an ifdef to support other compilers

#define chiLogInfo(str,...) chiWriteLog_int(CHI_INFO,__FUNCTION__,__LINE__,str,##__VA_ARGS__)
#define chiLogWarn(str,...) chiWriteLog_int(CHI_WARN,__FUNCTION__,__LINE__,str,##__VA_ARGS__)
#define chiLogError(str,...) chiWriteLog_int(CHI_ERROR,__FUNCTION__,__LINE__,str,##__VA_ARGS__)
#define chiLogFatal(str,...) chiWriteLog_int(CHI_FATAL,__FUNCTION__,__LINE__,str,##__VA_ARGS__)
#define chiLogVerbose(str,...) chiWriteLog_int(CHI_VERBOSE,__FUNCTION__,__LINE__,str,##__VA_ARGS__)
