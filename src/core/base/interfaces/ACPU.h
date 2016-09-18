//
// Created by Alexei Gladkikh on 18/09/16.
//

#ifndef MSP430EMU_ICPU_H
#define MSP430EMU_ICPU_H

#include <cstdint>
#include <memory>
#include <vector>

namespace vmc {
    class ACPU {
    protected:
        uint32_t _pc = 0;
        std::vector<uint32_t> _regs;
    public:
        uint32_t pc() { return _pc; };

        uint32_t reg(int indx) { return _regs[indx]; }
        void reg(int indx, uint32_t value) { _regs[indx] = value; }
    };

    typedef std::shared_ptr<ACPU> PACPU;
}

#endif //MSP430EMU_ICPU_H
