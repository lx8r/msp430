//
// Created by Alexei Gladkikh on 18/09/16.
//

#ifndef MSP430EMU_PROCESSOR_H
#define MSP430EMU_PROCESSOR_H

#include <stdint.h>
#include <string>
#include "Message.h"
#include "INetwork.h"
#include "../helpers/helpers.h"
#include "../core/base/interfaces/IDebuggable.h"

namespace gdb {
    class RequestProcessor : public helpers::ARunnableThread {
        bool _isProcessing = false;
        PINetwork client = nullptr;
        PIDebuggable target = nullptr;
        Message gdbMessage;

        void run() override;

        void processStep();
        void processRegisterWrite(int reg, uint32_t val);
        void ProcessSetAllOpThread(int thId);
        void ProcessSetContinueThread(int thId);
        void processContinue();
        void processContinue(int signal);
        void processReadMem(uint32_t address, int len);
        void processKillRequest();
        void processRegisterRead(int reg);
        void processAllRegistersRead();
        void processGeneralRequest(std::string message);
        void processExtendedRequest(std::string message);
        void processHaltReason();
        void processExtendedDebugRequest();
        void processCmdDefault();
        void processSetBpt(bpt::Type bpType, uint32_t address, uint8_t count);
        void processClearBpt(bpt::Type bpType, uint32_t address, uint8_t count);
    public:
        bool isProcessing() { return _isProcessing; };

        RequestProcessor(PINetwork client, PIDebuggable target, Message message) :
                gdbMessage(message),
                target(target),
                client(client),
                ARunnableThread() { }

        void halt();
    };

    typedef std::shared_ptr<RequestProcessor> PRequestProcessor;
}


#endif //MSP430EMU_PROCESSOR_H
