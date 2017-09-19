#ifndef __SELECT_REACTOR_IMPL__
#define __SELECT_REACTOR_IMPL__

#include "ReactorImpl.h"
#include "DemuxTable.h"

class SelectReactorImpl : public ReactorImpl
{
public:
    virtual void registerHandler(EventHandler *eh, EventType et);
    virtual void removeHandler(EventHandler *eh, EventType et);
    virtual void handleEvents(unsigned int timeout = 0);

    virtual ~SelectReactorImpl();

private:
    DemuxTable mDemuxTable;
};

#endif //__SELECT_REACTOR_IMPL__