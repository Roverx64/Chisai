#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include "chisai.h"

FILE *logfl;
char *logStrings[5];
char *logFormat = NULL;
uint64_t logOptions = 0x0;

/*
Log format options
f = function name
n = log level
l = line
t = time
m = string
*/

void setLoggingFormat(char *format){
    logFormat = format;
}

int enableFileLogging(const char *path, bool create){
    logfl = fopen(path,(create) ? "w+" : "w");
    if(logfl == NULL){return -1;}
    logOptions |= LOG_OPT_FILE_OUT;
    return 0;

}

void setLogLevelStrings(char *general, char *info, char *warn, char *error, char *fatal){
    logStrings[0] = general;
    logStrings[1] = info;
    logStrings[2] = warn;
    logStrings[3] = error;
    logStrings[4] = fatal;
}

void setLogOptions(uint64_t opt){
    logOptions = opt;
}

void writeLog(int level, const char *func, int line, const char *str, ...){
    //Parse format
    //NOTE: It's probably possible to optimize this more
    va_list list;
    va_start(list,str);
    time_t tm;
    struct tm *tinf;
    for(int i = 0; logFormat[i] != '\0'; ++i){
        if(logFormat[i] != '%'){
            if(!(logOptions&LOG_OPT_NO_STDOUT)){printf("%c",logFormat[i]);}
            if(logOptions&LOG_OPT_FILE_OUT){fprintf(logfl,"%c",logFormat[i]);}
            continue;
        }
        ++i;
        switch(logFormat[i]){
            case '%':
            if(!(logOptions&LOG_OPT_NO_STDOUT)){printf("%%");}
            if(logOptions&LOG_OPT_FILE_OUT){fputs("%",logfl);}
            break;
            //Function name
            case 'f':
            if(!(logOptions&LOG_OPT_NO_STDOUT)){printf("%s",func);}
            if(logOptions&LOG_OPT_FILE_OUT){fprintf(logfl,"%s",func);}
            break;
            //Log level
            case 'n':
            if((level > 4) || (level < 0)){level = 0;}
            if(!(logOptions&LOG_OPT_NO_STDOUT)){printf("%s",logStrings[level]);}
            if(logOptions&LOG_OPT_FILE_OUT){fprintf(logfl,"%s",logStrings[level]);}
            break;
            //Line number
            case 'l':
            if(!(logOptions&LOG_OPT_NO_STDOUT)){printf("%i",line);}
            if(logOptions&LOG_OPT_FILE_OUT){fprintf(logfl,"%i",line);}
            break;
            //POSIX time
            case 't':
            time(&tm);
            tinf = localtime(&tm);
            if(!(logOptions&LOG_OPT_NO_STDOUT)){printf("%i:%i:%i",tinf->tm_hour,tinf->tm_min,tinf->tm_sec);}
            if(logOptions&LOG_OPT_FILE_OUT){fprintf(logfl,"%i:%i:%i",tinf->tm_hour,tinf->tm_min,tinf->tm_sec);}
            break;
            //Message
            case 'm':
            if(!(logOptions&LOG_OPT_NO_STDOUT)){vprintf(str,list);}
            if(logOptions&LOG_OPT_FILE_OUT){vfprintf(logfl,str,list);}
            break;
        }
    }
}

void closeLog(){
    if(logOptions|LOG_OPT_FILE_OUT){fclose(logfl);}
}
