//
// Created by Alexei Gladkikh on 18/09/16.
//

#ifndef MSP430EMU_AOPERAND_H
#define MSP430EMU_AOPERAND_H

#include <cstdint>
#include <memory>

namespace vmc {
    class ADevice;
    typedef std::shared_ptr<ADevice> PADevice;

    class IOperand {
    public:
        virtual uint32_t value(PADevice dev) = 0;
        virtual void value(PADevice dev, uint32_t data) = 0;
        virtual std::string stringify() = 0;
    };

    typedef std::shared_ptr<IOperand> PIOperand;
}

#endif //MSP430EMU_AOPERAND_H
