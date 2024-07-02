#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include "chisai.h"

FILE *logfl;
char *logStrings[6];
char *logFormat = NULL;
uint32_t logOptions = 0x0;

/*
Log format options
f = function name
n = log level
l = line
t = time
m = string
*/

void chiSetLoggingFormat(char *format){
    logFormat = format;
}

int chiEnableFileLogging(const char *path, bool create){
    logfl = fopen(path,(create) ? "w+" : "w");
    if(logfl == NULL){return -1;}
    logOptions |= CHI_OPT_FILE_OUT;
    return 0;

}

void chiSetLogStrings(char *general, char *info, char *warn, char *error, char *fatal, char *verbose){
    logStrings[CHI_GENERAL] = general;
    logStrings[CHI_INFO] = info;
    logStrings[CHI_WARN] = warn;
    logStrings[CHI_ERROR] = error;
    logStrings[CHI_FATAL] = fatal;
    logStrings[CHI_VERBOSE] = verbose;
}

void chiSetLoggingLevel(uint8_t level){
    logOptions = CHI_OPT_SET_LOG_LEVEL(logOptions,level);
}

void chiSetLogOptions(uint32_t opt){
    if(logOptions&CHI_OPT_FILE_OUT){opt |= CHI_OPT_FILE_OUT;}
    logOptions = opt;
}

void chiWriteLog_int(int level, const char *func, int line, const char *str, ...){
    //Parse format
    //NOTE: It's probably possible to optimize this more
    if((level < 0) || (level > CHI_FATAL)){level = CHI_GENERAL;}
    if(CHI_OPT_GET_LOG_LEVEL(logOptions) > level){return;}
    va_list list;
    va_start(list,str);
    time_t tm;
    struct tm *tinf;
    for(int i = 0; logFormat[i] != '\0'; ++i){
        if(logFormat[i] != '%'){
            if(!(logOptions&CHI_OPT_NO_STDOUT)){printf("%c",logFormat[i]);}
            if(logOptions&CHI_OPT_FILE_OUT){fprintf(logfl,"%c",logFormat[i]);}
            continue;
        }
        ++i;
        switch(logFormat[i]){
            case '\0':
            return;
            break;
            case '%':
            if(!(logOptions&CHI_OPT_NO_STDOUT)){printf("%%");}
            if(logOptions&CHI_OPT_FILE_OUT){fputs("%",logfl);}
            break;
            //Function name
            case 'f':
            if(!(logOptions&CHI_OPT_NO_STDOUT)){printf("%s",func);}
            if(logOptions&CHI_OPT_FILE_OUT){fprintf(logfl,"%s",func);}
            break;
            //Log level
            case 'n':
            if(!(logOptions&CHI_OPT_NO_STDOUT)){printf("%s",logStrings[level]);}
            if(logOptions&CHI_OPT_FILE_OUT){fprintf(logfl,"%s",logStrings[level]);}
            break;
            //Line number
            case 'l':
            if(!(logOptions&CHI_OPT_NO_STDOUT)){printf("%i",line);}
            if(logOptions&CHI_OPT_FILE_OUT){fprintf(logfl,"%i",line);}
            break;
            //POSIX time
            case 't':
            time(&tm);
            tinf = localtime(&tm);
            if(!(logOptions&CHI_OPT_NO_STDOUT)){printf("%i:%i:%i",tinf->tm_hour,tinf->tm_min,tinf->tm_sec);}
            if(logOptions&CHI_OPT_FILE_OUT){fprintf(logfl,"%i:%i:%i",tinf->tm_hour,tinf->tm_min,tinf->tm_sec);}
            break;
            //Message
            case 'm':
            if(!(logOptions&CHI_OPT_NO_STDOUT)){vprintf(str,list);}
            if(logOptions&CHI_OPT_FILE_OUT){vfprintf(logfl,str,list);}
            break;
        }
    }
}

void chiCloseLog(){
    if(logOptions|CHI_OPT_FILE_OUT){fclose(logfl);}
}