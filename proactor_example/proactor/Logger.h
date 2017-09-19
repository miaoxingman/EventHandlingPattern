#ifndef __LOGGER__
#define __LOGGER__
#include <chrono>
#include <ctime>
#include <iomanip>
#include <mutex>
#include <string>
#include <sstream>
#include <thread>
#include <iostream>

class Logger
{
private:
    static std::mutex sMutex;
    Logger() {}

    static std::string dateToString(
            const std::chrono::system_clock::time_point p) {
        const std::time_t convTime = std::chrono::system_clock::to_time_t(p);
        std::tm timetm = *std::localtime(&convTime);
        std::stringstream oss;
        oss << std::put_time(&timetm, "%c %Z");
        return oss.str();
    };

    static std::string dateToString(
            const std::chrono::system_clock::time_point& start,
            const std::chrono::system_clock::time_point& end) {
        std::stringstream oss;
        oss << dateToString(start);
        std::chrono::milliseconds milliStart = 
            std::chrono::duration_cast<std::chrono::milliseconds>(
                start.time_since_epoch());
        std::chrono::milliseconds milliEnd   = 
            std::chrono::duration_cast<std::chrono::milliseconds>(
                end.time_since_epoch());
        oss << " - elapsed: " << milliEnd.count() - milliStart.count() << " ms";
        return oss.str();
    }

public:
    template<typename T> static std::string toStr(T t) {
        std::stringstream os;
        os << t;
        return os.str();
    };
    static void log(const std::string &message,
                    std::ostream& ostr = std::cout) {
        std::lock_guard<std::mutex> locker(sMutex);
        ostr << message << std::endl << std::flush;
    }

    static void log(const std::string& message,
                    const long long operationId,
                    const std::thread::id threadId,
                    const std::chrono::system_clock::time_point& time) {
        log(message + toStr(operationId) +
                " \t[thread: " + toStr(threadId) +
                "] (" + dateToString(time) + ")");
    }

    static void log(const std::string& message,
                    const long long operationId,
                    const std::thread::id threadId,
                    const std::chrono::system_clock::time_point& startTime,
                    const std::chrono::system_clock::time_point& endTime) {
        log(message + toStr(operationId) +
                " \t[thread: " + toStr(threadId) + "] (" +
                dateToString(startTime, endTime) + ")");
    };
};

#endif //__LOGGER__