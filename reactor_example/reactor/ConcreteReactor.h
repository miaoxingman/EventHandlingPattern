#ifndef __CONCRETE_REACTOR_H__
#define __CONCRETE_REACTOR_H__

#include "Reactor.h"

class ConcreteReactor : public Reactor
{
public:
    ConcreteReactor();
    ~ConcreteReactor();

    virtual void registerHandler(EventHandler *eh, EventType et);
    virtual void removeHandler(EventHandler *eh, EventType et);

    void handleEvents(unsigned int timeout = 0);
};
#endif //__CONCRETE_REACTOR_H__