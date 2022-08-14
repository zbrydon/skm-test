#ifndef logging_h
#define logging_h

#include "terminal.h"
#include <chrono>
#include <ctime>
#include <fstream>

namespace splashkit_lib
{

    /**
     *    defines the available log levels for log messages.
     * @constant NONE         Output to the message log but without a specified level
     * @constant INFO         Output information to the message log
     * @constant DEBUG        Output a debug message to the message log
     * @constant WARNING    Output a warning message to the message log
     * @constant ERROR        Output an error message to the message log
     * @constant FATAL        Output an error message to the message log
     */
    enum log_level {
        NONE,
        INFO,
        DEBUG,
        WARNING,
        ERROR,
        FATAL
    };
    
    /**
     *    Defines the available modes of logging.
     * @constant NONE Set the logging mode to none for nothing to be logged to the console or a file.
     * @constant CONSOLE Ensure that output only directs to the on-screen, text-based console..
     * @constant FILE Ensure that output only directs to a text file..
     * @constant CONSOLE_AND_FILE Direct ouput to both the console and a file.
    */
    enum log_mode
    {
        CONSOLE,
        FILE_ONLY,
        CONSOLE_AND_FILE
    };
    
    /**
     * This Function is overloaded.
     * changes the logging mode between either writing to a file or both a file and the text-based console.
     * @param app_name The name of the application being written requiring logging
     * @param override_prev_log Determines whether or not a new logging session should override the existing file, if any.    Set this to false if you want new log messages to be appended to the bottom of the file; otherwise set it to true if you would like a new file to be created on top of the old one.  
     * @param mode The mode of log output i.e. whether there should be output to the console, a text file, or both.  Pass your choice of mode variable in by reference.
     */
        void init_custom_logger (string app_name, bool override_prev_log, log_mode mode);

    /**
     * This Function is overloaded.
     * changes the logging mode for logged messages to be written to the text-based console.
true if you would like a new file to be created on top of the old one.  
     * @param mode The mode of log output i.e. whether there should be output to the console, a text file, or both.  Pass your choice of mode variable in by reference.
     */
        void init_custom_logger (log_mode mode);

    /**
     * Send a message to the message log. The message will be written if the log level for
     * the program is set to display this.
     * 
     * @param level         The level of the message to log
     * @param message     The message to be shown
     */
    void log(log_level level, string message);
    
    /**
     * Ensures propper memory clean-up prior to exit, if needed.  Used in sk_init_looging ().
    */
    void close_log_process ();
}
#endif
