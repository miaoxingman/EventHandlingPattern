#ifndef __REACTOR_IMPL_H__
#define __REACTOR_IMPL_H__

#include "EventHandler.h"

class ReactorImpl
{
public:
    virtual void registerHandler(EventHandler *eh, EventType et) = 0;
    virtual void removeHandler(EventHandler *eh, EventType et) = 0;
    virtual void handleEvents(unsigned int timeout = 0) = 0;

    virtual ~ReactorImpl() {};
};

#endif //__REACTOR_IMPL_H__