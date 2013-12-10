#ifndef SIMPLESERVER_LOG_H
#define SIMPLESERVER_LOG_H

#define LOG(X,Y...) Log::msg(Log::X, __FILE__, __LINE__,Y)
#define SET_LOG_TYPE(X,Y) Log::set_log_type(Log::X,Y)
#define LOG_STRING_SIZE 1024
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

namespace simpleserver {
/**
 * Represents a singleton logger. All logging should be done via the LOG() macro
 * to eliminate the need to manually use __FILE__ and __LINE__. Likewise,
 * toggling of specific message types should be set using the SET_LOG_TYPE()
 * macro to prevent having to use class namespace.
 *
 * Example Usage:
 *   LOG(ERROR, "Error Message %d", 24601);
 * Outputs Something Like:
 *   2013-11-06T21:31:29Z [ERROR:log_test.cpp:16] Error Message 24601
 */
class Log {
  public:
    // enum containing all tpyes of messages to log, TYPE_SIZE must be last.
    enum TYPE { ERROR, WARNING, INFO, DEBUG, STATS, TYPE_SIZE };

    /**
     * Toggle a specific type of logging on or off. Should be accessed via macro
     * at beginning of file.
     *
     * @param type the type of Logging to turn on or off
     * @param value the value to set the type of logging to
     */
    static void set_log_type(TYPE type, bool value) {
      Log::get_instance().bools[type] = value;
    }

    /**
     * Log various message types. Should be accessed via macro at beginning of
     * file.
     *
     * @param type the type of message to log
     * @param *source the source file it occurred in
     * @param line the line number it occurred on
     * @param *msg a printf style string
     * @param ... any trailing variables for vsprintf to use
     */
    static void msg(TYPE type, const char *source, int line, const char *msg, ...) {
      // if we are not logging this type of message, return
      if (!Log::get_instance().bools[type])
        return;

      // create a va_list of the trailing variables and log the message
      va_list args;
      va_start(args, msg);

      // create a string for the message type
      char type_string[16];
      switch(type) {
        case ERROR:
          strncpy(type_string, "ERROR", sizeof(type_string));
          break;
        case WARNING:
          strncpy(type_string, "WARNING", sizeof(type_string));
          break;
        case INFO:
          strncpy(type_string, "INFO", sizeof(type_string));
          break;
        case DEBUG:
          strncpy(type_string, "DEBUG", sizeof(type_string));
          break;
        case STATS:
          strncpy(type_string, "STATS", sizeof(type_string));
          break;
        default:
          strncpy(type_string, "UNKNOWN", sizeof(type_string));
          break;
      }

      // strip the source of its path
      while (strstr(source, "/") != NULL)
        source = strstr(source, "/") + 1;

      // create a combined date and time string in ISO 8601 format
      time_t rawtime = time(NULL);
      strftime(Log::get_instance().log_string, LOG_STRING_SIZE, "%Y-%m-%dT%H:%M:%SZ", gmtime(&rawtime));

      // record the passed in values for type of message, source file, and line number
      sprintf(Log::get_instance().log_string + strlen(Log::get_instance().log_string), " [%s:%s:%d] ", type_string, source, line);

      // record the passed in variables and append a newline
      vsprintf(Log::get_instance().log_string + strlen(Log::get_instance().log_string), msg, args);
      strcpy(Log::get_instance().log_string + strlen(Log::get_instance().log_string), "\n");

      // log the generated message and free the va_list
      fprintf(stdout, "%s", Log::get_instance().log_string);
      va_end(args);
    }

  private:
    char log_string[LOG_STRING_SIZE]; // string used to generate log message.
    bool bools[TYPE_SIZE]; // Boolean array storing state of Log types.

    /**
     * Constructor, set alllogging to on.
     */
    Log() {
      for (int i = 0; i < TYPE_SIZE; i++)
        bools[i] = true;
    }

    /**
     * Get the singleton instance of the Log object.
     *
     * @return a pointer to the singleton instance of the Log object
     */
    static Log& get_instance() {
      static Log instance;
      return instance;
    }
};
}
#endif // ifndef SIMPLESERVER_LOG_H
