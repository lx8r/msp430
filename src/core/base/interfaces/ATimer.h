//
// Created by Alexei Gladkikh on 18/09/16.
//

#ifndef MSP430EMU_ITIMER_H
#define MSP430EMU_ITIMER_H

#include <cstdint>
#include <memory>

namespace vmc {
    class ATimer {
    protected:
        uint64_t _ticks = 0;
    public:
        virtual void update(uint64_t ticks) = 0;
        uint64_t ticks() { return _ticks; };
    };

    typedef std::shared_ptr<ATimer> PATimer;
}

#endif //MSP430EMU_ITIMER_H
