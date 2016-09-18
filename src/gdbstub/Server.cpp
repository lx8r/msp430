//
// Created by Alexei Gladkikh on 18/09/16.
//

#include "Server.h"
#include "../thirdparty/easylogging/easylogging++.h"

#define log el::Loggers::getLogger("gdbServer")

gdb::Server::Server(int port, PIDebuggable target) {
#ifdef __WIN32__
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2);
    errid = WSAStartup(wVersionRequested, &wsaData);
    if (errid) {
        log->error("WSAStartup failed: %d\n", errid);
        return false;
    }
#endif

    this->port = port;
    this->target = target;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        log->error("Can't create socket...");
        throw std::bad_exception();
    }

    log->info("Socket created successfully");

    const socklen_t len = sizeof(struct sockaddr_in);
    memset(&sa, 0, len);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    int status = bind(serverSocket, (struct sockaddr*) &sa, len);
    if (status == -1) {
        log->error("Bind socket failed...");
        close(serverSocket);
        throw std::bad_exception();
    }

    log->info("Socket bind successfully");

    listen(serverSocket, 3);
}

void gdb::Server::doListen() {
    bool done = false;
    while (!done) {
        log->info("Waiting for incoming connection...");
        socklen_t len = sizeof(struct sockaddr_in);
        int clientSocket = accept(serverSocket, (struct sockaddr *) &sa, &len);
        if (clientSocket >= 0) {
            log->info("Connection accepted successfully");
            clientThread = std::make_shared<ClientThread>(clientSocket, target);
            clientThread->join();
        } else {
            log->error("Accept failed: %d", clientSocket);
        }
    }
}