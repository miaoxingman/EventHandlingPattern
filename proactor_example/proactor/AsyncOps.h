#ifndef __ASYNC_OPS__
#define __ASYNC_OPS__
#include <chrono>
#include <memory>
#include <thread>

#include "Observer.h"
#include "Logger.h"

template <typename T>
class AsyncOps
{
private:
    static unsigned long sOpsId;

protected:
    T mResult;
    bool executed;
    const unsigned long mOpsId;
    std::chrono::system_clock::time_point mStartTime;
    std::chrono::system_clock::time_point mStopTime;
    Observer<AsyncOps<T>>* mObserver;

    AsyncOps() : mResult(), executed(false), mOpsId(++sOpsId),
        mStartTime(), mStopTime(), mObserver(NULL) {
        };

    virtual void executeOperation() = 0;
    virtual ~AsyncOps(){};

public:
    void setObserver (Observer<AsyncOps<T>>* observer) {
        mObserver = observer;
    }

    void execute() {
        mStartTime = std::chrono::system_clock::now();
        Logger::log("\tStarting operation ", mOpsId,
            std::this_thread::get_id(), mStartTime);

        // Use the template pattern
        executeOperation();

        mStopTime = std::chrono::system_clock::now();
        Logger::log("\tFinished operation ",
            mOpsId, std::this_thread::get_id(), mStartTime, mStopTime);

        if (mObserver != NULL)
            mObserver->notify(this);
        }

    const unsigned int getId() const {
        return mOpsId;
    };

    virtual T getResult() const = 0;
};

template <typename T> unsigned long AsyncOps<T>::sOpsId = 0;

#endif //__ASYNC_OPS__













