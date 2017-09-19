#ifndef __INITATOR_H__
#define __INITATOR_H__
#include <future>
#include <memory>
#include <chrono>
#include <thread>

#include "AsyncOps.h"
#include "AsyncOpsProcessor.h"
#include "CompletionEventQueue.h"
#include "Observer.h"
#include "Proactor.h"
#include "Logger.h"

template <typename T>
class Initator : public Observer<AsyncOps<T>> {
private:
    std::shared_ptr<CompletionEventQueue<T>> mCompletionEventQueue;
    std::shared_ptr<AsyncOpsProcessor<T>>    mAsyncOpsProcessor;
    std::unique_ptr<Proactor<T>>             mProactor;
    std::future<void>                        mProactorThread;

public:
    Initator() :
    mCompletionEventQueue(std::shared_ptr<CompletionEventQueue<T>>(new CompletionEventQueue<T>())),
    mAsyncOpsProcessor(std::make_shared<AsyncOpsProcessor<T>>(mCompletionEventQueue)),
    mProactor(std::unique_ptr<Proactor<T>>(new Proactor<T>(mCompletionEventQueue, this))) {
        mProactorThread = std::async(std::launch::async, &Proactor<T>::exec, mProactor.get());
}

    virtual ~Initator() {
        while (mCompletionEventQueue->size() != 0) {
        Logger::log("Waiting for last elements...: " + Logger::toStr(mCompletionEventQueue->size()));
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        mProactor->canFinish(true);
        mProactorThread.wait();
        Logger::log("Finished InitiatorCompletion.");
    }

    void processOperation(AsyncOps<T> *ops) {
        Logger::log("Initiating operation " + Logger::toStr(ops->getId()) + "... ");
        mAsyncOpsProcessor->addOperation(ops);
    }

    void notify(AsyncOps<T>* ops) {
        Logger::log("Notified in Initiator/Completion - id:" +
                Logger::toStr(ops->getId()) +
                " - Result operation: " +
                Logger::toStr(ops->getResult()));
    }

};

#endif //__INITATOR_H__