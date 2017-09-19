#ifndef __LOG_EVENT_ACCEPTOR__
#define __LOG_EVENT_ACCEPTOR__

#include <string>
#include <set>
#include "Reactor.h"
#include "SocketAcceptor.h"
#include "LogEventHandler.h"

class LogEventAcceptor : public EventHandler
{
public:
    LogEventAcceptor(short port, Reactor *reactor);
    ~LogEventAcceptor();

    virtual void handleEvent(int handle, EventType et);
    virtual int getHandle() const;
    void clearInvalidEventHandler();

private:
    std::set<std::shared_ptr<LogEventHandler>> mEventHandlers;
    SocketAcceptor              mAcceptor;
    Reactor*                    mReactor;
};

#endif //__LOG_EVENT_ACCEPTOR__