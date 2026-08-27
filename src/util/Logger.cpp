#include <Bliss/Logger.h>
#include <iostream>

#ifdef __ANDROID__
    #include <android/log.h>
#endif

std::string format(const char* fmt, va_list args) {
    va_list args, temp;
    va_copy(temp, args);
    
    int size = std::vsnprintf(nullptr, 0, fmt, temp);
    va_end(temp);

    std::string str;
    str.resize(size+1);

    std::vsnprintf(str.data(), str.size(), fmt, args);

    return str;
}

void Logger::Verbose(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    std::string str = format(fmt, args);
    va_end(args);

    #ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_VERBOSE, TAG, str.c_str());
    #else
        str = "[VERBOSE] " + str;
        puts(str.c_str());
    #endif
}

void Logger::Debug(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    std::string str = format(fmt, args);
    va_end(args);

    #ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_DEBUG, TAG, str.c_str());
    #else
        str = "[DEBUG] " + str;
        puts(str.c_str());
    #endif
}

void Logger::Info(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    std::string str = format(fmt, args);
    va_end(args);

    #ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_INFO, TAG, str.c_str());
    #else
        str = "[INFO] " + str;
        puts(str.c_str());
    #endif
}

void Logger::Warn(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    std::string str = format(fmt, args);
    va_end(args);

    #ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_WARN, TAG, str.c_str());
    #else
        str = "[WARN] " + str;
        puts(str.c_str());
    #endif
}

void Logger::Error(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    std::string str = format(fmt, args);
    va_end(args);

    #ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_ERROR, TAG, str.c_str());
    #else
        str = "[ERROR] " + str;
        puts(str.c_str());
    #endif
}

void Logger::Fatal(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    std::string str = format(fmt, args);
    va_end(args);

    #ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_FATAL, TAG, str.c_str());
    #else
        str = "[FATAL] " + str;
        puts(str.c_str());
    #endif
}

void Logger::Silent(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    std::string str = format(fmt, args);
    va_end(args);

    #ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_SILENT, TAG, str.c_str());
    #else
        str = "[SILENT] " + str;
        puts(str.c_str());
    #endif
}

void Logger::Print(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    std::string str = format(fmt, args);
    va_end(args);

    #ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_UNKNOWN, TAG, str.c_str());
    #else
        puts(str.c_str());
    #endif
}