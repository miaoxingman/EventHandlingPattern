#include "LogEventAcceptor.h"
#include "SocketStream.h"
#include "LogEventHandler.h"
#include <iostream>

LogEventAcceptor::LogEventAcceptor(short port,
                                   Reactor *reactor) :
        mAcceptor(port),
        mReactor(reactor) {
    mReactor->registerHandler(this, ACCEPT_EVENT);
}

LogEventAcceptor::~LogEventAcceptor() {
    mEventHandlers.clear();
}

void LogEventAcceptor::handleEvent(int handle, EventType et) {
    if (et == ACCEPT_EVENT) {
        auto client = std::make_shared<SocketStream>();
        mAcceptor.accept(*client);
        //TODO:
        //add the handler into a list and clear these handler with a timer

        std::shared_ptr<LogEventHandler> handler(new LogEventHandler(client, mReactor));
        handler->isAlive();
        mEventHandlers.insert(handler);
    }
}

void LogEventAcceptor::clearInvalidEventHandler() {
    auto iter = mEventHandlers.begin();
    for (; iter != mEventHandlers.end();) {
        if((*iter)->isAlive()) {
            ++iter;
        } else {
            iter = mEventHandlers.erase(iter);
        }
    }
}

int LogEventAcceptor::getHandle() const {
    return mAcceptor.getHandle();
}