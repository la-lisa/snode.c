#ifndef BASECONNECTEDSOCKET_H
#define BASECONNECTEDSOCKET_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#include "SocketConnection.h"


class SocketServer;

template <typename Reader, typename Writer>
class SocketConnectionBase
    : public SocketConnection
    , public Reader
    , public Writer {
public:
    virtual void enqueue(const char* buffer, int size) override;
    virtual void enqueue(const std::string& junk) override;
    virtual void end() override;

    virtual void stashReader() override;
    virtual void unstashReader() override;

    virtual void stashWriter() override;
    virtual void unstashWriter() override;

    virtual InetAddress& getRemoteAddress() override;
    virtual void setRemoteAddress(const InetAddress& remoteAddress) override;

private:
    virtual void unmanaged() override;

protected:
    SocketConnectionBase(int csFd, SocketServer* serverSocket,
                         const std::function<void(SocketConnection* cs, const char* junk, ssize_t n)>& readProcessor,
                         const std::function<void(SocketConnection* cs, int errnum)>& onReadError,
                         const std::function<void(SocketConnection* cs, int errnum)>& onWriteError);

    SocketServer* serverSocket;

    InetAddress remoteAddress;
};

#endif // BASECONNECTEDSOCKET_H
