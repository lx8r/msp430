#include "thirdparty/easylogging/easylogging++.h"

INITIALIZE_EASYLOGGINGPP

#include "gdbstub/Server.h"
#include "targets/Dummy.h"

#define log el::Loggers::getLogger("main")

int main(int argc, char* argv[]) {
    log->info("MSP430 Virtual machine started");
    auto target = std::make_shared<targets::Dummy>();
    auto server = gdb::Server(27026, target);
    server.doListen();
    return 0;
}
