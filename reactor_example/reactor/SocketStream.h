#ifndef __SOCKET_STREAM__
#define __SOCKET_STREAM__

#include <stddef.h> //size_t

class SocketStream
{
public:
    SocketStream();
    SocketStream(int handle);
    ~SocketStream();

    void closeSocket();
    void setHandle(int handle);
    int getHandle() const;
    size_t recv(char* buf, size_t len, int flags);
    size_t send(const char* buf, size_t len, int flags);

private:
    int mHandle;
};

#endif //__SOCKET_STREAM__