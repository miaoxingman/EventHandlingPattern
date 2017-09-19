#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

#include "EventType.h"
#include <memory>
// single-method interface.
class EventHandler : public std::enable_shared_from_this<EventHandler>
{
public:
    // Hook method dispatched by Reactor to handle event of a particular type.
    virtual void handleEvent(int handle, EventType et) = 0;
    //Hook method that returns the I/O HANDLE.
    virtual int getHandle() const = 0;

    virtual ~EventHandler() {};
};

#endif //__EVENT_HANDLER_H__