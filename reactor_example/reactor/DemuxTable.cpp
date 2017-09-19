#include "DemuxTable.h"

void DemuxTable::ConvertToFDSets(fd_set *readFds,
                                 fd_set *writeFds,
                                 fd_set *exceptFds) {
    FD_ZERO(readFds);
    FD_ZERO(writeFds);
    FD_ZERO(exceptFds);

    DemuxTable::iterator iter = this->begin();

    for (; iter != this->end(); iter++) {
        if (iter->second.type == READ_EVENT ||
           iter->second.type == ACCEPT_EVENT) {
            FD_SET(iter->first, readFds);
        } else if (iter->second.type == WRITE_EVENT) {
            FD_SET(iter->first, writeFds);
        } else if (iter->second.type == SIGNAL_EVENT) {
            FD_SET(iter->first, exceptFds);
        } else {
            throw std::invalid_argument("Event_type not supported.");
        }
    }
}