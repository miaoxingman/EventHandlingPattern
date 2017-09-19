#ifndef __REACTOR_H__
#define __REACTOR_H__

#include "EventHandler.h"
#include "ReactorImpl.h"

class Reactor
{
public:
    //Methods that register and remove EventHandler of particular EventType.
    virtual void registerHandler(EventHandler *eh, EventType et) = 0;
    //virtual void registerHandler(int handle, EventHandler *eh, EventType et) = 0;
    virtual void removeHandler(EventHandler *eh, EventType et) = 0;
    //virtual void removeHandler(int handle, EventType et) = 0;

    //Entry point into the reactive event loop.
    virtual void handleEvents(unsigned int timeout = 0) = 0;

    //define a singleton access point
    static Reactor* instance();

protected:
    Reactor(ReactorImpl* reactor_impl);
    //Use the Bridge pattern to hold a pointer to the implemenataion.
    ReactorImpl* mReactorImpl; 
};

#endif // __REACTOR_H__