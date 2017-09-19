#include "LogEventHandler.h"
#include <iostream>

LogEventHandler::LogEventHandler(std::shared_ptr<SocketStream> socket, Reactor *reactor) :
    mSocketStream(socket),
    mReactor(reactor) {
        mReactor->registerHandler(this, READ_EVENT);
        mIsAlive = true;
    }

LogEventHandler::~LogEventHandler() {
    //
}

void LogEventHandler::handleEvent(int handle, EventType et) {
    if(et == READ_EVENT) {
        char buf[1024];
        memset(buf, 0, 1024);
        int result = mSocketStream->recv(buf, 1024, 0);
        if(result == 0) {
            std::cout<<"connection closed"<<std::endl;
            mReactor->removeHandler(this, et);
            mIsAlive = false;
            return;
        }
        std::cout<<"[recv] "<<buf;
    } else if(et == TIMEOUT_EVENT){
    } else {
        std::cout<<"error from LogEventHandler"<<et<<std::endl;
    }
}

int LogEventHandler::getHandle() const {
    //
    return mSocketStream->getHandle();
}

bool LogEventHandler::isAlive() const {
    return mIsAlive;
}