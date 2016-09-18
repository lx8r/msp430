//
// Created by Alexei Gladkikh on 18/09/16.
//

#ifndef MSP430EMU_IDEVICE_H
#define MSP430EMU_IDEVICE_H

#include "ACPU.h"
#include "IMemory.h"
#include "IMMU.h"
#include "ATimer.h"
#include "AInstruction.h"
#include "IDecoder.h"

namespace vmc {
    class ADevice {
    protected:
        PACPU cpu = nullptr;
        PIMemory memory = nullptr;
        PIMMU mmu = nullptr;
        PATimer timer = nullptr;
        PIDecoder decoder = nullptr;
    public:
        bool execute() {
            uint32_t word = memory->loadWord(cpu->pc());
            PAInstruction insn = decoder->decode(word);
            uint32_t ticks = insn->execute(PADevice(this));
            timer->update(ticks);
            return true;
        }
    };

    typedef std::shared_ptr<ADevice> PADevice;
}

#endif //MSP430EMU_IDEVICE_H
