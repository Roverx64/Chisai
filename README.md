## About
Chisai is a simple and basic logging tool primarily for use with my projects.  
Using Chisai is fairly simple and the available functions are described below.

## Functions

#### `setLoggingFormat(char *format)`
Sets the format the logger should use
```c
setLoggingFormat("%f:%l[%t][%n]: %m");
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

#### `enableFileLogging(const char *path, bool create)`
Attempts to open, or create, a file at the specified path.  
Returns `-1` on failure.  
```c
enableFileLogging("./myLog.log",true);
```

---

#### `setLogLevelStrings(char *general, char *info, char *warn, char *error, char *fatal)`
Sets the strings to use when `%n` is used.  
```c
setLogLevelStrings("G","I","W","E","F");
//Or
setLogLevelStrings("General","Info","Warn","Error","Fatal");
```

---

#### `void setLogOptions(uint64_t opt)`
Sets the logging options to use.  
Available options defined below.  
```c
setLogOptions(LOG_OPT_NO_STDOUT);
```
OR these together.  
|Name                |Description                |
|--------------------|---------------------------|
|LOG_OPT_FILE_OUT    |Internal use only          |
|LOG_OPT_NO_STDOUT   |Disables printing to stdout|

---

#### `writeLog(int level, const char *func, int line, const char *str, ...)`
Writes to the log. The first three arguments are set automatically with `LOG_...`  
Log types are specified below.  
```c
writeLog(LOG_INFO,"Initilized log %i\n",0);
```

|Level         |Description                                         |
|--------------|----------------------------------------------------|
|LOG_GENEAL    |Used when the level is outside of the accepted range|
|LOG_INFO      |Log general info                                    |
|LOG_WARN      |Log warnings                                        |
|LOG_ERROR     |Log errors                                          |
|LOG_FATAL     |Log fatal errors                                    |

---

#### `closeLog()`
Closes the opened log file if one is open
