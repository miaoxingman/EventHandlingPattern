#ifndef __PROACTOR_H__
#define __PROACTOR_H__
#include <memory>
#include "CompletionEventQueue.h"
#include "AsyncOps.h"
#include "Observer.h"
#include "Logger.h"

template <typename T>
class Proactor {
private:
    bool mFinish;
    std::shared_ptr<CompletionEventQueue<T>> mCompletionEventQueue;
    Observer<AsyncOps<T>> *mObserver;

public:
    Proactor(std::shared_ptr<CompletionEventQueue<T>> ceq,
        Observer<AsyncOps<T>>* o) : mCompletionEventQueue(ceq), mObserver(o),
            mFinish(false){};

    virtual ~Proactor() {
        Logger::log("Proactor finish. ");
    }

    void canFinish(const bool finish) {
        this->mFinish = finish;
    }

    void exec() {
        while (!mFinish || mCompletionEventQueue->arePendingOps()) {
            while ((mCompletionEventQueue->size() == 0) && (!mFinish)) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                if (mCompletionEventQueue->size() > 0) {
                    Logger::log("Proactor removes element from queue");
                    AsyncOps<T> *ops = mCompletionEventQueue->pop();
                    mObserver->notify(ops);
                }
            }
        }
        Logger::log("Proactor execution finished.");
    }
};

#endif //__PROACTOR_H__