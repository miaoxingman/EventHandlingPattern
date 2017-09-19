#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <iostream>

#include "SocketAcceptor.h"

SocketAcceptor::SocketAcceptor(short port) {
    mHandle = 0;
    open(port);
}

SocketAcceptor::~SocketAcceptor() {
    if (mHandle) {
        close(mHandle);
    }
}

void SocketAcceptor::accept(SocketStream& s) {
    s.setHandle(::accept(mHandle, 0, 0));
}

int SocketAcceptor::getHandle() const {
    return mHandle;
}

void SocketAcceptor::open(short port) {

    struct sockaddr_in server_addr;

    if(mHandle) {
        close(mHandle);
    }

    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(port);

    mHandle = socket(PF_INET, SOCK_STREAM, 0);
    if (!mHandle) {
        std::cout<<"create socket failed"<<std::endl;
        exit(1);
    }

    int optval = 1;
    if (setsockopt(mHandle, SOL_SOCKET, SO_REUSEADDR,
        &optval, sizeof(optval)) == -1) {
        std::cout << "Error setting SO_REUSEADDR option" << std::endl;
    }

    if (bind(mHandle, (struct sockaddr*)&server_addr, sizeof(sockaddr_in)) == 0) {
#ifdef ENABLE_DEBUG_MACRO
        std::cout << "Socket " << mHandle << " bind to "
                  << port << std::endl;
#endif
    } else {
        std::cout<<"bind socket failed"<<std::endl;
        exit(1);
    }

#ifdef ENABLE_DEBUG_MACRO
    std::cout<<"starting listen on port "<<port<<std::endl;
#endif

    if (listen(mHandle, 5) == -1) {
        std::cout << "Error when listening" << std::endl;
        return;
    }
}
