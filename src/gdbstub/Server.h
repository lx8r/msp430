//
// Created by Alexei Gladkikh on 18/09/16.
//

#ifndef MSP430EMU_SERVER_H
#define MSP430EMU_SERVER_H

#ifdef __WIN32__
#include <winsock2.h>
#include <windows.h>
typedef int socklen_t;
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#endif

#include "ClientThread.h"

namespace gdb {

    class Server {
        int port;
        int serverSocket;
        struct sockaddr_in sa;
        PIDebuggable target = nullptr;
        PClientThread clientThread = nullptr;
    public:
        Server(int port, PIDebuggable target);
        void doListen();
    };

}


#endif //MSP430EMU_SERVER_H
