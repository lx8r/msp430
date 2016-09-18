//
// Created by Alexei Gladkikh on 18/09/16.
//

#ifndef MSP430EMU_INETWORK_H
#define MSP430EMU_INETWORK_H

#include <stdint.h>
#include <cstddef>
#include "Message.h"

namespace gdb {
    class INetwork {
    public:
        virtual bool doSend(Message message) = 0;
        virtual void doRecv() = 0;
        virtual void doClose() = 0;
    };

    typedef std::shared_ptr<INetwork> PINetwork;
}

#endif //MSP430EMU_INETWORK_H
