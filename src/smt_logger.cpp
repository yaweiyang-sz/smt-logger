#include "smt_logger.h"
#include <cstdarg>

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <iostream>
#include <utility>
#include "spdlog/sinks/rotating_file_sink.h"

#ifdef __GNUC__
#define vsprintf_s vsnprintf
#endif

constexpr auto LOG_PATTEN =
    "[%Y-%m-%d %H:%M:%S.%e][%^%L%$][thread %t][module %n][tag %w]: %v";

constexpr auto LOG_PATTEN_NO_MODULE =
    "[%Y-%m-%d %H:%M:%S.%e][%^%L%$][thread %t][tag %w]: %v";

LoggerConfig mLoggerConfig = {"default", LogLevel::ERR, false, 3};

std::shared_ptr<spdlog::logger> getLogger();

void setupLogger(LoggerConfig config) { mLoggerConfig = std::move(config); }

void logDebug(std::string tag, const char *format, ...) {
  char buffer[256];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, 256, format, args);
  va_end(args);

  // print log
  getLogger()->debug(std::move(tag), buffer);
}

void logInfo(std::string tag, const char *format, ...) {
  char buffer[256];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, 256, format, args);
  va_end(args);

  // print log
  getLogger()->info(std::move(tag), buffer);
}

void logWarn(std::string tag, const char *format, ...) {
  char buffer[256];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, 256, format, args);
  va_end(args);

  // print log
  getLogger()->warn(std::move(tag), buffer);
}

void logError(std::string tag, const char *format, ...) {
  char buffer[256];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, 256, format, args);
  va_end(args);

  // print log
  getLogger()->error(std::move(tag), buffer);
}

void logTrace(std::string tag, const char *format, ...) {
  char buffer[256];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, 256, format, args);
  va_end(args);

  // print log
  getLogger()->trace(std::move(tag), buffer);
}

void logCritical(std::string tag, const char *format, ...) {
  char buffer[256];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, 256, format, args);
  va_end(args);

  // print log
  getLogger()->trace(std::move(tag), buffer);
}

spdlog::level::level_enum findMatchedLogLevel(LogLevel logLevel) {
  switch (logLevel) {
  case LogLevel::TRACE:
    return spdlog::level::trace;

  case LogLevel::DEBUG:
    return spdlog::level::debug;

  case LogLevel::INFO:
    return spdlog::level::info;

  case LogLevel::WARN:
    return spdlog::level::warn;

  case LogLevel::ERR:
    return spdlog::level::err;

  case LogLevel::CRITICAL:
    return spdlog::level::critical;

  default:
    return spdlog::level::off;
  };
}

std::shared_ptr<spdlog::logger> getLogger() {
  if (mLoggerConfig.module == "") {
    std::cout
        << "no module specified, please set it with `setupLogger(LoggerConfig)`"
        << std::endl;
    return nullptr;
  }

  // find exist logger
  auto logger = spdlog::get(mLoggerConfig.module);
  if (logger != nullptr) {
    return logger;
  }

  bool debugMode = false;
#ifdef LOG_DEBUG
  debugMode = true;
#endif // LOG_DEBUG

  // setup spdlog
  auto logLevel = findMatchedLogLevel(mLoggerConfig.logLevel);
  if (debugMode && !mLoggerConfig.logFileInDebugMode) {
    logger = spdlog::stdout_color_mt(mLoggerConfig.module);
  } else {
    // 5mb size max and 1 rotated file
    logger = spdlog::rotating_logger_mt(
            mLoggerConfig.module, "logs/" + mLoggerConfig.module + ".log",
        1024 * 1024 * 5, 1);
  }

  logger->set_level(logLevel);

  // don't print module when write file
  if (debugMode && !mLoggerConfig.logFileInDebugMode) {
    logger->set_pattern(LOG_PATTEN);
  } else {
    logger->set_pattern(LOG_PATTEN_NO_MODULE);
  }

  // set flush trigger level
  if (debugMode) {
    logger->flush_on(spdlog::level::trace);
  } else {
    logger->flush_on(spdlog::level::err);
  }

  // flushFrequency must bigger than zero
  if (mLoggerConfig.flushFrequency < 0) {
      mLoggerConfig.flushFrequency = 1;
  }
  spdlog::flush_every(std::chrono::seconds(mLoggerConfig.flushFrequency));
  return logger;
}