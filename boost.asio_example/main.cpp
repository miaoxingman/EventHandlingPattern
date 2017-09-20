#include <iostream>
#include "Remotery.h"

Remotery* rmt;

int main()
{
    rmt_CreateGlobalInstance(&rmt);
    std::cout<<"hello world !"<<std::endl;
    rmt_DestroyGlobalInstance(rmt);
}
