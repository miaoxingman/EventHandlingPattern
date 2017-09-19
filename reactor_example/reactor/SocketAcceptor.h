#ifndef __SOCKET_ACCEPTOR__
#define __SOCKET_ACCEPTOR__

#include <string>
#include "SocketStream.h"

class SocketAcceptor
{
public:
    SocketAcceptor(short port);
    ~SocketAcceptor();

    void accept(SocketStream& s);
    int getHandle() const;

private:
    void open(short port);
    int mHandle;
};

#endif //__SOCKET_ACCEPTOR__