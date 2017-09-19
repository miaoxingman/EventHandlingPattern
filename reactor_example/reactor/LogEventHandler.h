#ifndef __LOG_EVENT_HANDLER__
#define __LOG_EVENT_HANDLER__
#include <memory>
#include "Reactor.h"
#include "SocketStream.h"

class LogEventHandler : public EventHandler
{
public:
    LogEventHandler(std::shared_ptr<SocketStream> socket, Reactor *reactor);
    ~LogEventHandler();

    virtual void handleEvent(int handle, EventType et);
    virtual int getHandle() const;
    bool    isAlive() const;
private:
    std::shared_ptr<SocketStream>   mSocketStream;
    Reactor*                        mReactor;
    bool                            mIsAlive;
};

#endif //__LOG_EVENT_HANDLER__