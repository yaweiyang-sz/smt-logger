smt_logger
==========

A log warpper based on spdlog library, provide easier API to print logs at console and write logs into file.

## Basic Usage:

-------

```c++
#include "smt_logger.h"

int main(){
    // single param log
    logError("name1", "log message");

    // dynamic params log
    logError("name2", "dynamic params %s, %d", "abc", 123);

    return 0;
}
```

Log Result:

```shell

[2019-11-28 09:27:49.900][E][thread 25856][tag name1]: log message
[2019-11-28 09:27:49.913][E][thread 25856][tag name2]: dynamic params abc, 123, param2:abc
```

## How to build/install

-------

```shell
mkdir build
cd build

# -DCMAKE_BUILD_TYPE="Release" is optional
cmake .. -DCMAKE_BUILD_TYPE="Release"

# if you like, you can alse install it into `/usr/local/`
sudo make install
```

Note：DCMAKE_BUILD_TYPE is a optional parameter，the option parameters are below：

1. Release：it's the default type and also is the best performance build type.
2. Debug：low performance with log info.
3. MinSizeRel：the smallest size build type for embedded device.
4. RelWithDebInfo：similar with 'Release' type but print debug info.

## How to integrate

-------

Every release version zip contains a head file, two lib and so files.

```shell
// the only head file
smt_logger.h

// for release mode
smt_logger-1.0.lib/smt_logger-1.0.so

// for debug mode
smt_logger-1.0d.lib/smt_logger-1.0d.so
```

## Setup Logger

 -------

```c++
enum class LogLevel{
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERR,
    CRITICAL,
    OFF
};
```

`LogLevel::TRACE` is the lowest level.  
`LogLevel::OFF` is the highest level, which means if you set log level as some one, then only below(include that type) that types of logs will be printed at console or written into log file. 

```c++
struct LoggerConfig{

    /**
     * when print log into files, 
     * logs will print into every module log files.
     */
    std::string module;

    /**
     * default log level is ERR, which means logs will
     * not print if its level is below ERR .
     */
    LogLevel logLevel;

    /**
     * as defualt, log print to console not file,
     * but you can change it to log into file with this
     */
    bool logFileInDebugMode;

    /**
     * default file sync frequency is 5s, you can change it before
     * printing any logs
     */
    int flushFrequency;
};
void setupLogger(LoggerConfig);
```

## for example

```c++
LoggerConfig config ={"default", LogLevel::TRACE, false, 3};
setupLogger(config);

logTrace("tag0", "trace msg...");
logDebug("tag1", "debug msg...");
logInfo("tag2", "info msg...");
logWarn("tag3", "info msg...");
logError("tag4", "error msg...");
```
