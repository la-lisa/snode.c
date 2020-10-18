/*
 * snode.c - a slim toolkit for network communication
 * Copyright (C) 2020 Volker Christian <me@vchrist.at>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <climits>
#include <sys/select.h> // for fd_set
#include <sys/time.h>   // for timeval

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#include "AcceptEventDispatcher.h"
#include "ConnectEventDispatcher.h"
#include "FdSet.h"
#include "OutOfBandEventDispatcher.h"
#include "ReadEventDispatcher.h"
#include "TimerEventDispatcher.h"
#include "WriteEventDispatcher.h"

namespace net {

    class EventLoop {
    private:
        EventLoop();

    public:
        static EventLoop& instance() {
            return eventLoop;
        }

        // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays, hicpp-avoid-c-arrays, modernize-avoid-c-arrays)
        static void init(int argc, char* argv[]);
        static int start();
        static void stop();

        ReadEventDispatcher& getReadEventDispatcher() {
            return readEventDispatcher;
        }

        AcceptEventDispatcher& getAcceptEventDispatcher() {
            return acceptEventDispatcher;
        }

        ConnectEventDispatcher& getConnectEventDispatcher() {
            return connectEventDispatcher;
        }

        WriteEventDispatcher& getWriteEventDispatcher() {
            return writeEventDispatcher;
        }

        OutOfBandEventDispatcher& getOutOfBandEventDispatcher() {
            return outOfBandEventDispatcher;
        }

        TimerEventDispatcher& getTimerEventDispatcher() {
            return timerEventDispatcher;
        }

        unsigned long getEventCounter() {
            return readEventDispatcher.getEventCounter() + writeEventDispatcher.getEventCounter() +
                   acceptEventDispatcher.getEventCounter() + outOfBandEventDispatcher.getEventCounter() +
                   connectEventDispatcher.getEventCounter();
        }

        unsigned long getTickCounter() {
            return tickCounter;
        }

    private:
        static void stoponsig(int sig);

        inline void tick();

        static EventLoop eventLoop;

        FdSet readFdSet;
        FdSet writeFdSet;
        FdSet exceptFdSet;

        ReadEventDispatcher readEventDispatcher;
        AcceptEventDispatcher acceptEventDispatcher;
        WriteEventDispatcher writeEventDispatcher;
        OutOfBandEventDispatcher outOfBandEventDispatcher;
        ConnectEventDispatcher connectEventDispatcher;
        TimerEventDispatcher timerEventDispatcher;

        struct timeval nextInactivityTimeout = {LONG_MAX, 0};

        static bool running;
        static bool stopped;
        static int stopsig;
        static bool initialized;

        unsigned long tickCounter = 0;
    };

} // namespace net

#endif // EVENTLOOP_H
