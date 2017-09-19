#include "SelectReactorImpl.h"
#include <iostream>
SelectReactorImpl::~SelectReactorImpl() {
    //
}

void SelectReactorImpl::registerHandler(EventHandler *eh, EventType et) {
    DemuxTable::iterator iter = mDemuxTable.find(eh->getHandle());
    if (iter != mDemuxTable.end()) {
        delete iter->second.handler;
    }

    EventHandlerTuple eht;
    eht.handler = eh;
    eht.type = et;
    mDemuxTable[eh->getHandle()] = eht;
#ifdef ENABLE_DEBUG_MACRO
    std::cout<<"["<<__FUNCTION__<<"] "<<
        "register "<<eh->getHandle()<<" for "<< getEventString(et) <<std::endl;
#endif
}

void SelectReactorImpl::removeHandler(EventHandler *eh, EventType et) {
    DemuxTable::iterator iter = mDemuxTable.find(eh->getHandle());
    if (iter != mDemuxTable.end()) {
        mDemuxTable.erase(iter);
    }
}

void SelectReactorImpl::handleEvents(unsigned int timeout) {
    int max_fd = 0;
    fd_set read_set, write_set, except_set;

    timeval timeout_setting;
    timeout_setting.tv_sec = timeout;
    timeout_setting.tv_usec = 0;
    
    DemuxTable::reverse_iterator riter = mDemuxTable.rbegin();
    if (riter != mDemuxTable.rend()) {
        max_fd = riter->first + 1;
    }

    mDemuxTable.ConvertToFDSets(&read_set, &write_set, &except_set);
    int result = select(max_fd, &read_set, &write_set, &except_set, &timeout_setting);
    std::map<unsigned int, EventHandlerTuple> iterTable(mDemuxTable);
    if (result == -1) {
#ifdef ENABLE_DEBUG_MACRO
        std::cout<<"["<<__FUNCTION__<<"] "<<"select error"<<std::endl;
#endif
        throw std::runtime_error("select error");
    } else if (result == 0) {
        DemuxTable::iterator it = mDemuxTable.begin();
        for (; it != mDemuxTable.end(); it++) {
            it->second.handler->handleEvent(it->first, TIMEOUT_EVENT);
        }
    } else {
        DemuxTable::iterator it = mDemuxTable.begin();
        for (; it != mDemuxTable.end(); it++) {
            if (FD_ISSET((int)it->first, &read_set) ||
                FD_ISSET((int)it->first, &write_set) ||
                FD_ISSET((int)it->first, &except_set)) {
#ifdef ENABLE_DEBUG_MACRO
                std::cout<<"["<<__FUNCTION__<<"] "<<"select -> "<<
                    "("<<it->first<<") - "<<getEventString(it->second.type) <<std::endl;
#endif
                it->second.handler->handleEvent(it->first, it->second.type);
            }
        }
    }
}