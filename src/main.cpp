#include "thirdparty/easylogging/easylogging++.h"

INITIALIZE_EASYLOGGINGPP

#include "gdbstub/Server.h"
#include "core/dummy/Device.h"

#define log el::Loggers::getLogger("main")

int main(int argc, char* argv[]) {
    log->info("MSP430 Virtual machine started");
    auto target = std::make_shared<dummy::Device>();
    // auto server = gdb::Server(27026, target);
    // server.doListen();

    target->execute();

    return 0;
}
