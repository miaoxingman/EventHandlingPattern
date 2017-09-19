#ifndef __DEMUX_TABLE__
#define __DEMUX_TABLE__

#include <map>
#include <sys/select.h>

#include "EventHandler.h"

struct EventHandlerTuple
{
    EventHandler*   handler;
    EventType       type;
};

class DemuxTable : public std::map<unsigned int, EventHandlerTuple>
{
public:
    void ConvertToFDSets(fd_set *readFds, fd_set *writeFds, fd_set *exceptFds);
};

#endif