/**
 * @file TyLog_Qt.h
 * @brief TyLog For Qt
 *     You can get more help through the following way:
 *     1. My WebSite: http://tianyiyan.com
 *     2. GitHub: https://github.com/luckytianyiyan/TyClassLibrary
 *
 * @author luckytianyiyan@gmail.com
 * @version 1.0
 * @date 2015-8-24
 */
#ifndef __TYYLOG_QT_H__
#define __TYYLOG_QT_H__
#include <qlogging.h>
#include <QString>

#ifndef LOG_COLORS_ENABLE
    #define LOG_COLORS_ENABLE 1
#endif
/**
 * @brief 默认打印等级
 */
#ifndef LOG_LEVEL
    #define LOG_LEVEL LOG_LEVEL_DEBUG
#endif

#ifndef QT_DEBUG
    #undef LOG_LEVEL
    #define LOG_LEVEL LOG_LEVEL_NO
#endif

/**
 * @brief  Log Levels
 *
 *  LOG_LEVEL_DEBUG > LOG_LEVEL_INFO > LOG_LEVEL_WARN > LOG_LEVEL_CRITICAL > LOG_LEVEL_FATAL
 *
 *      TyLogDebug  >   TyLogInfo    >  TyLogWarning  >    TyLogCritical   > TyLogFatal
 *
 * @{
 */

#define LOG_FLAG_FATAL      (1 << 0)  // 0...00001
#define LOG_FLAG_CRITICAL   (1 << 1)  // 0...00010
#define LOG_FLAG_WARN       (1 << 2)  // 0...00100
#define LOG_FLAG_INFO       (1 << 3)  // 0...01000
#define LOG_FLAG_DEBUG      (1 << 4)  // 0...10000

#define LOG_LEVEL_NO        0
#define LOG_LEVEL_FATAL     (LOG_FLAG_FATAL)                          // 0...00001
#define LOG_LEVEL_CRITICAL  (LOG_FLAG_CRITICAL  | LOG_LEVEL_FATAL   ) // 0...00011
#define LOG_LEVEL_WARN      (LOG_FLAG_WARN      | LOG_LEVEL_CRITICAL) // 0...00111
#define LOG_LEVEL_INFO      (LOG_FLAG_INFO      | LOG_LEVEL_WARN    ) // 0...01111
#define LOG_LEVEL_DEBUG     (LOG_FLAG_DEBUG     | LOG_LEVEL_INFO    ) // 0...11111

#define LOG_FATAL       (LOG_LEVEL & LOG_FLAG_FATAL     )
#define LOG_CRITICAL    (LOG_LEVEL & LOG_FLAG_CRITICAL  )
#define LOG_WARN        (LOG_LEVEL & LOG_FLAG_WARN      )
#define LOG_INFO        (LOG_LEVEL & LOG_FLAG_INFO      )
#define LOG_DEBUG       (LOG_LEVEL & LOG_FLAG_DEBUG     )

/** @} */


#if LOG_COLORS_ENABLE
    #define SHELL_COLORS_ESCAPE "\033["

    #define SHELL_COLORS_RESET     SHELL_COLORS_ESCAPE "\33"

    #define COLOR_DEBUG "35m"
    #define COLOR_INFO "30m"
    #define COLOR_WARN "33m"
    #define COLOR_CRITICAL "31m"
    #define COLOR_FATAL "31m"

#else

    #define SHELL_COLORS_ESCAPE

    #define SHELL_COLORS_RESET

    #define COLOR_DEBUG
    #define COLOR_INFO
    #define COLOR_WARN
    #define COLOR_CRITICAL
    #define COLOR_FATAL

#endif
/** @} */

/**
 * @brief  Logs
 *
 * 1. TyLogDebug
 *      用于输出 Debug 信息
 * 2. TyLogInfo
 *      用于输出 可能需要注意的处理过程 信息
 * 3. TyLogWarning
 *      用于输出 警告 信息, 用于 **主动防御时捕获到非法值, 将其设为默认** 的时候输出提醒.
 * 4. TyLogCritical
 *      用于输出 错误 信息
 * 5. TyLogFatal
 *      用于输出 严重错误 信息
 * @{
 */

#define TyLogBase(prefix, color, fmt, ...) qDebug(SHELL_COLORS_ESCAPE color prefix fmt##SHELL_COLORS_RESET, ##__VA_ARGS__)

#define TyLogDetail(prefix, color, fmt, ...) qDebug(SHELL_COLORS_ESCAPE color prefix "<%s (%d)> " fmt##SHELL_COLORS_RESET, QString(__FILE__).section('/', -1).toUtf8().data(), __LINE__, ##__VA_ARGS__)

#define TyLog TyLogDetail

#if LOG_DEBUG
    #define TyLogDebug(fmt, ...) TyLog("[D] ", COLOR_DEBUG, fmt, ##__VA_ARGS__)
#else
    #define TyLogDebug(fmt, ...)
#endif

#if LOG_INFO
    #define TyLogInfo(fmt, ...) TyLog("[I] ", COLOR_INFO, fmt, ##__VA_ARGS__)
#else
    #define TyLogInfo(fmt, ...)
#endif

#if LOG_WARN
    #define TyLogWarning(fmt, ...) TyLog("[W] ", COLOR_WARN, fmt, ##__VA_ARGS__)
#else
    #define TyLogWarning(fmt, ...)
#endif

#if LOG_CRITICAL
    #define TyLogCritical(fmt, ...) TyLog("[C] ", COLOR_CRITICAL, fmt, ##__VA_ARGS__)
#else
    #define TyLogCritical(fmt, ...)
#endif

#if LOG_FATAL
    #define TyLogFatal(fmt, ...) TyLog("[F] ", COLOR_FATAL, fmt, ##__VA_ARGS__)
#else
    #define TyLogFatal(fmt, ...)
#endif

/** @} */

#endif ///< __TYYLOG_QT_H__
