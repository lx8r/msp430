//
// Created by Alexei Gladkikh on 18/09/16.
//

#include <iomanip>
#include "ClientThread.h"
#include "../thirdparty/easylogging/easylogging++.h"

#define log el::Loggers::getLogger("gdbClient")
#define BUFFER_SIZE 2048

void gdb::ClientThread::doRecv() {
    // receiving routine won't be blocked in case debugger sends us 0x03 signal to suspend.
    log->info("Receiving thread started!");
    running = true;
    ssize_t read = 0;

    uint8_t buffer[BUFFER_SIZE];

    while (running) {
        read = recv(clientSocket, buffer, BUFFER_SIZE, 0);

        if (read < 1) {
            log->info("Client has closed connection!");
            break;
        }

        if (read == 1) {
            //single-byte packets, processed differently

            //got acknowledge, all ok, ignoring
            if (buffer[0] == '+') {
                log->trace("Got acknowledge +");
                continue;
            }

            //got acknowledge, message rejected
            if (buffer[0] == '-') {
                log->warn("Client rejected last message!");
                continue;
            }

            if (buffer[0] == 0x03) {
                log->info("Interrupt requested!");
                // processing synchronously, no need for processing any other packets until interrupt
                target->halt();
                //TODO: replace "magic id" with const
                doSend(Message::error(0x02));
                waitRequestProcessing();
                continue;
            }
        }

        // we won't process any packets until we get any response from system, except 0x03, interrupt request
        if (worker->isProcessing()) {
            log->warn("Message ignored due to processing now");
            continue;
        }

        std::string msgPack((char*) buffer);
        log->trace("%s", msgPack.c_str());
        auto messages = helpers::split(msgPack, '$');

        // there THEORETICALLY can be more then one msg in packet due to connection problems, but it ruins sync, so
        // just ignore all messages except first one.
        for (auto message : messages) {
            if (message == "")
                continue;

            auto msgAndCrc = helpers::split(message, '#');
            if (msgAndCrc.size() != 2) {
                log->warn("Got more then one '#' symbol in message [" + message + "], skipping");
                continue;
            }

            auto msg = Message(msgAndCrc[0]);
            if (msg.cksum(msgAndCrc[1])) {
                // sync acknowledge
                doSend(Message::raw("+"));
                // async processing, no need for queue, we'll skip next messages until
                // the end of processing or until 0x03 interrupts shows up
                worker = std::make_shared<RequestProcessor>(PClientThread(this), target, message);
                break;
            } else {
                doSend(Message::raw("-"));
                break;
            }
        }
    }
    running = false;
}

bool gdb::ClientThread::doSend(Message message) {
    std::string packed = message.build();
    const char* data = packed.c_str();
    ssize_t err = send(clientSocket, (const uint8_t *) data, packed.size(), 0);
    return err > 0;
}

void gdb::ClientThread::doClose() {
    log->info("Stopping client thread...");
    running = false;
    worker->halt();
    waitRequestProcessing();
    close(clientSocket);
}

void gdb::ClientThread::waitRequestProcessing() {
    if (worker != nullptr)
        worker->join();
}
