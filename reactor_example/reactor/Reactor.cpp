#include "reactor.h"
#include "ConcreteReactor.h"

Reactor::Reactor(ReactorImpl* reactorImpl)
    : mReactorImpl(reactorImpl) {
}

Reactor* Reactor::instance() {
    //TODO: add a factory to break the dependance.
    static ConcreteReactor reactorInstance;
    return &reactorInstance;
}