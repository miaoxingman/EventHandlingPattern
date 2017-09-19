#include "ConcreteReactor.h"
#include "SelectReactorImpl.h"

ConcreteReactor::ConcreteReactor()
    : Reactor(new SelectReactorImpl()) {
}

ConcreteReactor::~ConcreteReactor() {
    delete mReactorImpl;
}

void ConcreteReactor::registerHandler(EventHandler *eh, EventType et) {
    mReactorImpl->registerHandler(eh, et);
}

void ConcreteReactor::removeHandler(EventHandler *eh, EventType et) {
    mReactorImpl->removeHandler(eh, et);
}

void ConcreteReactor::handleEvents(unsigned int timeout) {
    mReactorImpl->handleEvents(timeout);
}