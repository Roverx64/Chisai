#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include "chisai.h"

FILE *logfl;
bool logToFile = false;
char *logStrings[5];
char *logFormat = NULL;

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
    logToFile = true;
    return 0;

}

void setLogLevelStrings(char *general, char *info, char *warn, char *error, char *fatal){
    logStrings[0] = general;
    logStrings[1] = info;
    logStrings[2] = warn;
    logStrings[3] = error;
    logStrings[4] = fatal;
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
            printf("%c",logFormat[i]);
            if(logToFile){fprintf(logfl,"%c",logFormat[i]);}
            continue;
        }
        ++i;
        switch(logFormat[i]){
            case '%':
            printf("%%");
            if(logToFile){fputs("%",logfl);}
            break;
            //Function name
            case 'f':
            printf("%s",func);
            if(logToFile){fprintf(logfl,"%s",func);}
            break;
            //Log level
            case 'n':
            if((level > 4) || (level < 0)){level = 0;}
            printf("%s",logStrings[level]);
            if(logToFile){fprintf(logfl,"%s",logStrings[level]);}
            break;
            //Line number
            case 'l':
            printf("%i",line);
            if(logToFile){fprintf(logfl,"%i",line);}
            break;
            //POSIX time
            case 't':
            time(&tm);
            tinf = localtime(&tm);
            printf("%i:%i:%i",tinf->tm_hour,tinf->tm_min,tinf->tm_sec);
            if(logToFile){fprintf(logfl,"%i:%i:%i",tinf->tm_hour,tinf->tm_min,tinf->tm_sec);}
            break;
            //Message
            case 'm':
            vprintf(str,list);
            if(logToFile){vfprintf(logfl,str,list);}
            break;
        }
    }
}

void closeLog(){
    if(logToFile){fclose(logfl);}
}