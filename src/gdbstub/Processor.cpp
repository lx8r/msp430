//
// Created by Alexei Gladkikh on 18/09/16.
//

#include "Processor.h"
#include "../thirdparty/easylogging/easylogging++.h"
#include "../core/base/exceptions/exceptions.h"

#define log el::Loggers::getLogger("gdbProcessor")

void gdb::RequestProcessor::run() {
    _isProcessing = true;

    int reg = 0;
    uint32_t val = 0;
    auto msg = gdbMessage.data();
    auto cmd = msg[0];
    auto data = msg.substr(1);

    if (cmd == '!') {
        processExtendedDebugRequest();
    } else if (cmd == '?') {
        processHaltReason();
    } else if (cmd == 'q') {
        processGeneralRequest(msg);
    } else if (cmd == 'v') {
        processExtendedRequest(msg);
    } else if (cmd == 'p') {
        reg = (int) stoul(data, nullptr, 16);
        processRegisterRead(reg);
    } else if (cmd == 'P') {
        auto msgParts = helpers::split(data, '=');
        reg = (int) stoul(msgParts[0], nullptr, 16);
        val = ntohl(stoul(msgParts[1], nullptr, 16));
        processRegisterWrite(reg, val);
    } else if (cmd == 'g') {
        processAllRegistersRead();
    } else if (cmd == 'c') {
        processContinue();
    } else if (cmd == 'C') {
        int sigId = (int) stoul(data, nullptr, 16);
        processContinue(sigId);
    } else if (cmd == 's') {
        processStep();
    } else if (cmd == 'H') {
        //Inform that further operations applies to some thread
        //Hc - continue operations
        //Hg - all operations
        char op = data[0];
        int thId = (int) stoul(data.substr(1), nullptr, 16);
        if (op == 'c')
            ProcessSetContinueThread(thId);
        else if (op == 'g')
            ProcessSetAllOpThread(thId);
        else {
            log->warn("Got wrong op argument in message [%s]", msg.c_str());
            processCmdDefault();
        }
    } else if (cmd == 'm') {
        //read mem:         m addr,len
        auto bpParams = helpers::split(data, ',');
        if (bpParams.size() < 2) {
            log->warn("Got wrong number of parameters while reading mem!");
            log->warn("[%s]", msg.c_str());
            processCmdDefault();
        } else {
            uint32_t address = (uint32_t) stoul(bpParams[0], nullptr, 16);
            int count = (int) stoul(bpParams[1], nullptr, 16);
            processReadMem(address, count);
        }
    } else if (cmd == 'k') {
        processKillRequest();
    } else if (cmd == 'z') {
        //clear bp:         z type,address,count
        auto bpParams = helpers::split(data, ',');
        if (bpParams.size() < 3) {
            log->warn("Got wrong number of parameters while clearing BP!");
            log->warn("[%s]", msg.c_str());
            processCmdDefault();
        } else {
            uint8_t bpTypeValue = (uint8_t) stoul(bpParams[0], nullptr, 16);
            uint32_t address = (uint32_t) stoul(bpParams[1], nullptr, 16);
            int count = (int) stoul(bpParams[2], nullptr, 16);
            processClearBpt((bpt::Type) bpTypeValue, address, (uint8_t) count);
        }
    } else if (cmd == 'Z') {
        //set bp:         z type,address,count
        auto bpParams = helpers::split(data, ',');
        if (bpParams.size() < 3) {
            log->warn("Got wrong number of parameters while setting BP!");
            log->warn("[%s]", msg.c_str());
            processCmdDefault();
        } else {
            uint8_t bpTypeValue = (uint8_t) stoul(bpParams[0], nullptr, 16);
            uint32_t address = (uint32_t) stoul(bpParams[1], nullptr, 16);
            int count = (int) stoul(bpParams[2], nullptr, 16);
            processSetBpt((bpt::Type) bpTypeValue, address, (uint8_t) count);
        }
    } else {
        log->warn("Unknown message received: %s", msg.c_str());
        processCmdDefault();
    }
    _isProcessing = false;
}

void gdb::RequestProcessor::processRegisterWrite(int reg, uint32_t val) {
    log->trace("Request register %d write %08X", reg, val);
    client->doSend((target->writeRegister(reg, val)) ? Message::ok() : Message::error(0x00));
}

void gdb::RequestProcessor::processStep() {
    log->trace("Request single execute");
    target->step();
    uint8_t reason = target->haltReason();
    client->doSend(Message::interrupt(reason));
}

void gdb::RequestProcessor::ProcessSetAllOpThread(int thId) {
    log->trace("All further operations applies to thread [0x%x]", thId);
    client->doSend(Message::ok());
}

void gdb::RequestProcessor::ProcessSetContinueThread(int thId) {
    log->trace("Further continue operations applies to thread [0x%x]", thId);
    client->doSend(Message::ok());
}

void gdb::RequestProcessor::processContinue() {
    processContinue(5);
}

void gdb::RequestProcessor::processContinue(int signal) {
    log->trace("Request continue with signal = %02X", signal);
    target->run();
    uint8_t reason = target->haltReason();
    client->doSend(Message::interrupt(reason));
}

void gdb::RequestProcessor::processReadMem(uint32_t address, int len) {
    log->trace("Request 0x%02x bytes at [%08x]", len, address);
    try {
        auto data = target->readMemory(address, len);
        client->doSend(Message::bytes(data));
    } catch (exc::MemoryUnavailableException e) {
        log->warn("Error reading 0x%02x bytes at [%08x] -> %s", len, address, e.what());
        //TODO: replace err magic value with something
        client->doSend(Message::error(0x01));
    }
}

void gdb::RequestProcessor::processKillRequest() {
    target->kill();
    client->doClose();
}

void gdb::RequestProcessor::processClearBpt(bpt::Type bpType, uint32_t address, uint8_t count) {
    log->trace("Clearing %d-bytes %d breakpoint at [%08x]", count, bpType, address);
    client->doSend((target->clearBreakpoint(bpType, address, count)) ? Message::ok() : Message::empty());
}

void gdb::RequestProcessor::processSetBpt(bpt::Type bpType, uint32_t address, uint8_t count) {
    log->trace("Setting %d-bytes %d breakpoint at [%08x]", count, bpType, address);
    client->doSend((target->setBreakpoint(bpType, address, count)) ? Message::ok() : Message::empty());
}

void gdb::RequestProcessor::processExtendedRequest(std::string message) {
    client->doSend(Message::empty());
}

void gdb::RequestProcessor::processGeneralRequest(std::string message) {
    client->doSend(Message::empty());
}

void gdb::RequestProcessor::processAllRegistersRead() {
    log->trace("Request read all registers");
    std::list<uint32_t> values = target->readRegisters();
    client->doSend(Message::dwords(values));
}

void gdb::RequestProcessor::processRegisterRead(int reg) {
    log->trace("Request register %d read", reg);
    uint32_t value = htonl(target->readRegister(reg));
    client->doSend(Message::dword(value));
}

void gdb::RequestProcessor::processHaltReason() {
    log->trace("Request halt reason");
    uint8_t reason = target->haltReason();
    client->doSend(Message::interrupt(reason));
}

void gdb::RequestProcessor::processExtendedDebugRequest() {
    client->doSend(Message::ok());
}

void gdb::RequestProcessor::processCmdDefault() {
    client->doSend(Message::empty());
}

void gdb::RequestProcessor::halt() {
    target->halt();
}


