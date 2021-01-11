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

#include "ReadEventReceiver.h"

#include "DescriptorEventDispatcher.h"
#include "EventLoop.h"

namespace net {

    ReadEventReceiver::ReadEventReceiver(long timeout)
        : DescriptorEventReceiver(timeout) {
    }

    void ReadEventReceiver::setTimeout(long timeout) {
        DescriptorEventReceiver::setTimeout(timeout);
    }

    void ReadEventReceiver::dispatchEvent() {
        readEvent();
    }

    void ReadEventReceiver::enable(int fd) {
        EventLoop::instance().getReadEventDispatcher().enable(this, fd);
    }

    void ReadEventReceiver::disable() {
        EventLoop::instance().getReadEventDispatcher().disable(this, fd);
    }

    void ReadEventReceiver::suspend() {
        EventLoop::instance().getReadEventDispatcher().suspend(this, fd);
    }

    void ReadEventReceiver::resume() {
        EventLoop::instance().getReadEventDispatcher().resume(this, fd);
    }

} // namespace net
