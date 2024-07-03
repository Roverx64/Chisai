## About
Chisai is a tiny and basic logging tool primarily for use with my projects.  
Using Chisai is fairly simple and the available functions are described below.
  
---
### NOTE: Chisai uses a GCC specific macro: `##__VA_ARGS__`
#### I have not tested if other compilers recognize or use this macro the same way GCC does   

## Functions

#### `chiSetLoggingFormat(char *format)`
Sets the format the logger should use
```c
chiSetLoggingFormat("%f:%l[%t][%n]: %m");
chiLofInfo("Initilized log\n");
//Prints out like
//main:56[13:53:1][I]: Initilized log
```
The options to use are specified below

|Option|Description                    |
|------|-------------------------------|
|f     |Function name                  |
|l     |Line number                    |
|t     |POSIX time (hour:minute:second)|
|n     |Log level string               |
|m     |Message to print               |

---

#### `chiEnableFileLogging(const char *path, bool create)`
Attempts to open, or create, a file at the specified path.  
Returns `-1` on failure.  
```c
chiEnableFileLogging("./myLog.log",true);
```

---

#### `chiSetLogStrings(char *general, char *info, char *warn, char *error, char *fatal, char *verbose)`
Sets the strings to use when `%n` is used.  
```c
chiSetLogStrings("G","I","W","E","F","V");
//Or
chiSetLogStrings("General","Info","Warn","Error","Fatal","Verbose");
```

---

#### `chiSetLoggingLevel(uint8_t level)`  
Sets the minimum level to be printed.  
```c
chiSetLoggingLevel(CHI_FATAL);
chiLogFatal("This will be printed");
chiLogInfo("This won't be printed");
```

---

#### `chiSetLogOptions(uint32_t opt)`
Sets the logging options to use.  
Available options defined below.  
```c
chiSetLogOptions(CHI_OPT_NO_STDOUT);
```
OR these together.  
|Name                |Description                |
|--------------------|---------------------------|
|CHI_OPT_FILE_OUT    |Internal use only          |
|CHI_OPT_NO_STDOUT   |Disables printing to stdout|

---

#### `chiWriteLog_int(int level, const char *func, int line, const char *str, ...)`
Used interally by the macros.  
Writes to the log.
Log levels are specified below.  
```c
chiWriteLog_int(CHI_LEVEL_INFO,__FUNCTION__,__LINE__,"Initilized log %i\n",0);
//
//Macros that you should use instead
//
chiLogInfo();
chiLogWarn();
chiLogError();
chiLogFatal();
chiLogVerbose();
```

|Level         |Description                                         |
|--------------|----------------------------------------------------|
|CHI_GENERAL   |Used when the level is outside of the accepted range|
|CHI_VERBOSE   |Log verbose info                                    |
|CHI_INFO      |Log general info                                    |
|CHI_WARN      |Log warnings                                        |
|CHI_ERROR     |Log errors                                          |
|CHI_FATAL     |Log fatal errors                                    |

---

#### `chiCloseLog()`
Closes the opened log file if one is open
