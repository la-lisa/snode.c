#ifndef SOCKETREADER_H
#define SOCKETREADER_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <functional>

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#include "socket/SocketReaderBase.h"
#include "socket/legacy/Socket.h"


class SocketConnection;

namespace legacy {

    class SocketReader
        : public SocketReaderBase
        , virtual public legacy::Socket {
    public:
        using legacy::Socket::recv;
        ssize_t recv(char* junk, const ssize_t& junkSize);

    protected:
        SocketReader() {
        }

        SocketReader(const std::function<void(::SocketConnection* cs, const char* junk, ssize_t n)>& readProcessor,
                     const std::function<void(int errnum)>& onError)
            : legacy::Socket()
            , SocketReaderBase(readProcessor, onError) {
        }
    };

}; // namespace legacy

#endif // SOCKETREADER_H
