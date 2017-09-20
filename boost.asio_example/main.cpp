#include <iostream>
#include <unistd.h>
#include "demo_api.h"

Remotery* rmt;

int main()
{
    rmt_CreateGlobalInstance(&rmt);

    //sleep for 10 seconds
    sleep(10);
    std::cout << "wait for remotery to connect" << std::endl;

    boost_asio_demo();

    rmt_DestroyGlobalInstance(rmt);
}
