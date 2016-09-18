//
// Created by Alexei Gladkikh on 18/09/16.
//

#ifndef MSP430EMU_IINSTRUCTION_H
#define MSP430EMU_IINSTRUCTION_H

#include <cstdint>
#include <memory>
#include "IOperand.h"

namespace vmc {
    class AInstruction {
    public:
        uint32_t ea;
        uint32_t flags;
        PIOperand op1;
        PIOperand op2;
        virtual uint32_t execute(PADevice dev) = 0;
        virtual std::string stringify() = 0;
    };

    typedef std::shared_ptr<AInstruction> PAInstruction;
}

#endif //MSP430EMU_IINSTRUCTION_H
