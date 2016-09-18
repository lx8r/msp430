//
// Created by Alexei Gladkikh on 18/09/16.
//

#ifndef MSP430EMU_IMMU_H
#define MSP430EMU_IMMU_H

#include <cstdint>

namespace vmc {
    class IMMU {
        virtual uint32_t translate(uint32_t vAddr) = 0;
    };

    typedef std::shared_ptr<IMMU> PIMMU;
}

#endif //MSP430EMU_IMMU_H
