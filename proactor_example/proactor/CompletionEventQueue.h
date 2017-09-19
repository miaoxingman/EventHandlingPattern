#ifndef __COMPLETION_EVENT_QUEUE_H__
#define __COMPLETION_EVENT_QUEUE_H__
#include <deque>
#include <mutex>
#include "AsyncOps.h"

template<typename T>
class CompletionEventQueue : private std::deque<AsyncOps<T>*> {
private:
    std::mutex mMutex;
    unsigned int mPendingOps;

public:
    CompletionEventQueue() : std::deque<AsyncOps<T>*>(), mPendingOps(0) {
    };

    virtual ~CompletionEventQueue() {
        this->clear();
    };

    void push(AsyncOps<T>* ops) {
        std::lock_guard<std::mutex> locker(mMutex);

        this->push_back(ops);
        if (mPendingOps == 0) {
            throw std::exception();
        }
        --mPendingOps;
    };

    AsyncOps<T>* pop() {
        std::lock_guard<std::mutex> locker(mMutex);

        AsyncOps<T>* p = this->front();
        this->pop_front();
        return p;
    };

    const size_t size() {
        std::lock_guard<std::mutex> locker(mMutex);
        return std::deque<AsyncOps<T>*>::size();
    };

    void increasePendingOps() {
        std::lock_guard<std::mutex> locker(mMutex);
        ++mPendingOps;
    };

    bool arePendingOps() {
        std::lock_guard<std::mutex> locker(mMutex);
        return (mPendingOps == 0);
    };
};

#endif //__COMPLETION_EVENT_QUEUE_H__












