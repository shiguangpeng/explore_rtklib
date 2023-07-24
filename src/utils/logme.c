//
// Created by okyousgp on 2023/7/24.
//
#include "logme.h"

#include <stdio.h>
#include <time.h>

void logMessage(LogLevel level, const char* message) {
    time_t now = time(NULL);
    struct tm* timeinfo = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    const char* color;
    const char* msgType;
    switch (level) {
        case DEBUG:
            color = "\033[1;36m"; // Cyan
            msgType = "[DEBUG]";
            break;
        case INFO:
            color = "\033[1;32m"; // Green
            msgType = "[INFO]";
            break;
        case WARNING:
            color = "\033[1;33m"; // Yellow
            msgType = "[WARNING]";
            break;
        case ERRORS:
            color = "\033[1;31m"; // Red
            msgType = "[ERRORS]";
            break;
        default:
            color = "\033[0m"; // Default color
            msgType = "[Default]";
            break;
    }
    printf("\n%s[%s] %s %s%s\033[0m\n", color, timestamp, msgType, color, message);
}
#ifdef DEBUGMODE
int main(void) {
    logMessage(DEBUG, "This is a debug message.");
    logMessage(INFO, "This is an info message.");
    logMessage(WARNING, "This is a warning message.");
    logMessage(ERRORS, "This is an error message.");
    return 0;
}
#endif