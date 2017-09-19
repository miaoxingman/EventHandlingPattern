#ifndef __SUM_ASYNC_OPS_H__
#define __SUM_ASYNC_OPS_H__
#include <chrono>
#include <list>
#include <thread>
#include "AsyncOps.h"

template<typename T>
class SumAsyncOps : public AsyncOps<T> {
private:
    std::list<T> mElememts;
public:
    SumAsyncOps(std::list<T> numbers) {
        mElememts = numbers;
        AsyncOps<T>::executed = false;
    }
    ~SumAsyncOps() {
        mElememts.clear();
    }
    void executeOperation() {
        AsyncOps<T>::mResult = 0;
        for (T element : mElememts) {
            AsyncOps<T>::mResult += element;
            std::this_thread::sleep_for(std::chrono::milliseconds(std::rand() % 10000));
            AsyncOps<T>::executed = true;
        }
    }

    T getResult() const {
        if(AsyncOps<T>::executed) {
            return AsyncOps<T>::mResult;
        }
        throw std::exception();
    }
};

#endif //__SUM_ASYNC_OPS_H__