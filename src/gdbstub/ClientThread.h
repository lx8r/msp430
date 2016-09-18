//
// Created by Alexei Gladkikh on 18/09/16.
//

#ifndef MSP430EMU_CLIENTTHREAD_H
#define MSP430EMU_CLIENTTHREAD_H

#ifdef __WIN32__
#include <winsock2.h>
#include <windows.h>
typedef int socklen_t;
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif

#include <unistd.h>
#include <stdint.h>
#include <string>
#include "../interfaces/IDebuggable.h"
#include "../helpers/helpers.h"
#include "Message.h"
#include "INetwork.h"
#include "Processor.h"

namespace gdb {

    class ClientThread : public helpers::ARunnableThread, public INetwork {
    private:
        int clientSocket;
        bool running = false;
        PRequestProcessor worker = nullptr;
        PIDebuggable target = nullptr;

        bool doSend(Message message) override;
        void doRecv() override;
        void doClose() override;

        void run() override {
            doRecv();
        }

        void waitRequestProcessing();
    public:
        ClientThread(int socket, PIDebuggable target) :
                clientSocket(socket),
                target(target),
                helpers::ARunnableThread() { }
    };

    typedef std::shared_ptr<ClientThread> PClientThread;
}

#endif //MSP430EMU_CLIENTTHREAD_H
