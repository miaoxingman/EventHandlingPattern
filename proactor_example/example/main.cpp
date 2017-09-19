#include <iostream>
#include "SumAsyncOps.h"
#include "Initator.h"
#include "Logger.h"

int main()
{
    SumAsyncOps<int> op1 = SumAsyncOps<int>({10, 11});
    SumAsyncOps<int> op2 = SumAsyncOps<int>({12, 13});
    SumAsyncOps<int> op3 = SumAsyncOps<int>({14, 15});
    SumAsyncOps<int> op4 = SumAsyncOps<int>({16, 17});
    SumAsyncOps<int> op5 = SumAsyncOps<int>({18, 19});
    SumAsyncOps<int> op6 = SumAsyncOps<int>({20, 21});

    Logger::log("Starting operations execution...");
    Initator<int> initor;

    initor.processOperation(&op1);
    initor.processOperation(&op2);
    initor.processOperation(&op3);
    initor.processOperation(&op4);
    initor.processOperation(&op5);
    initor.processOperation(&op6);
    
    Logger::log("Done.");
    return 0;
}
