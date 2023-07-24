//
// Created by okyousgp on 2023/7/24.
//

#ifndef EXPLORE_RTKLIB_LOGME_H      // 防止头文件重复包含
#define EXPLORE_RTKLIB_LOGME_H

typedef enum {
    DEBUG,
    INFO,
    WARNING,
    ERRORS
} LogLevel;
#endif //EXPLORE_RTKLIB_LOGME_H

/**
 * @brief Records log messages
 * @param level Log level, possible values are DEBUG, INFO, WARNING, ERROR or default
 * @param message Log message content
 * @return None
 */

extern void logMessage(LogLevel level, const char* message);