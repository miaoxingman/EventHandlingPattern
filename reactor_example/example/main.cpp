#include <iostream>
#include "Reactor.h"
#include "LogEventAcceptor.h"

const short LOG_PORT= 10034;

int main()
{
    Reactor *reactor = Reactor::instance();
    LogEventAcceptor logEventAcceptor(LOG_PORT, reactor);

#ifdef ENABLE_DEBUG_MACRO
    std::cout<<"start handling event"<<std::endl;
#endif

    while(1) {
        reactor->handleEvents(1);
    }

    return 0;
}