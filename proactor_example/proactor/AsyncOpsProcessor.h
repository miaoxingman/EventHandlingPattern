#ifndef __ASYNC_OPS_PROCESSOR_H__
#define __ASYNC_OPS_PROCESSOR_H__
#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include "AsyncOps.h"
#include "CompletionEventQueue.h"

template <typename T>
class AsyncOpsProcessor : public Observer<AsyncOps<T>>{
private:
    size_t mPoolSize;
    std::mutex mMutex;
    std::condition_variable mCV;
    std::deque<AsyncOps<T>*> mPool;
    std::shared_ptr<CompletionEventQueue<T>> mCompleteEventQueue;

public:
    static const size_t DEFAULT_QUEUE_SIZE = 2;
    AsyncOpsProcessor(std::shared_ptr<CompletionEventQueue<T>> & completeEventQueue,
        const size_t poolSize = DEFAULT_QUEUE_SIZE) :
            mPoolSize(poolSize),
            mPool(std::deque<AsyncOps<T>*>()),
            mCompleteEventQueue(completeEventQueue) {};
    virtual ~AsyncOpsProcessor(){};

    void addOperation(AsyncOps<T>* ops) {
            std::unique_lock<std::mutex> locker(mMutex);

        if(mPool.size() == mPoolSize) {
            mCV.wait(locker, [&] {return mPool.size() < mPoolSize;});
        }

        ops->setObserver(this);

        mCompleteEventQueue->increasePendingOps();

        std::thread t = std::thread(&AsyncOps<T>::execute, ops);
        t.detach();

        mPool.push_back(ops);
    }

    void notify(AsyncOps<T>* ops) {
         typedef typename std::deque<AsyncOps<T>*>::iterator iterType;
        std::unique_lock<std::mutex> locker(mMutex);

        mCompleteEventQueue->push(ops);
        bool full = false;

        iterType iter = std::find(mPool.begin(), mPool.end(), ops);
        if (iter != mPool.end()) {
            full = mPool.size() == mPoolSize;
            mPool.erase(iter);
        }

        if(full) {
            mCV.notify_one();
        }
    }
};

#endif //__ASYNC_OPS_PROCESSOR_H__