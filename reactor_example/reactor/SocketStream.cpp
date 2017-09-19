#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include "SocketStream.h"

SocketStream::SocketStream() : mHandle(0) {
}

SocketStream::SocketStream(int handle) : mHandle(handle) {
}

SocketStream::~SocketStream() {
    std::cout<<"SocketStream::~SocketStream called"<<std::endl;
    if(mHandle) {
       close(mHandle); 
    } 
}

void SocketStream::closeSocket() {
    if(mHandle) {
       close(mHandle); 
    }
}

void SocketStream::setHandle(int handle) {
    closeSocket();
    mHandle = handle;
}

int SocketStream::getHandle() const {
    return mHandle;
}

size_t SocketStream::recv(char* buf, size_t len, int flags) {
    return ::recv(mHandle, buf, len, flags);
}

size_t SocketStream::send(const char* buf, size_t len, int flags) {
    return ::send(mHandle, buf, len, flags);
}