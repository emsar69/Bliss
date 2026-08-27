#include <cstdarg>

namespace Logger {
    inline const char* TAG = "Bliss";

    void Verbose(const char* fmt, ...);
    void Debug(const char* fmt, ...);
    void Info(const char* fmt, ...);
    void Warn(const char* fmt, ...);
    void Error(const char* fmt, ...);
    void Fatal(const char* fmt, ...);
    void Silent(const char* fmt, ...);


    void Print(const char* fmt, ...);
}