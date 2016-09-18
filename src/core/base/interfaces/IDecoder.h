//
// Created by Alexei Gladkikh on 18/09/16.
//

#ifndef MSP430EMU_IDECODER_H
#define MSP430EMU_IDECODER_H

#include "AInstruction.h"

namespace vmc {
    class IDecoder {
    public:
        virtual PAInstruction decode(uint32_t data) = 0;
    };

    typedef std::shared_ptr<IDecoder> PIDecoder;
}

#endif //MSP430EMU_IDECODER_H
