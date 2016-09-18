//
// Created by Alexei Gladkikh on 18/09/16.
//

#ifndef MSP430EMU_SYSTEMTIMER_H
#define MSP430EMU_SYSTEMTIMER_H

#include <cstdint>
#include "../../base/interfaces/ATimer.h"

namespace dummy {
    class SystemTimer : public vmc::ATimer {
    public:
        void update(uint64_t ticks) override {
            throw exc::UnimplementedException();
        }
    };
}

#endif //MSP430EMU_SYSTEMTIMER_H
