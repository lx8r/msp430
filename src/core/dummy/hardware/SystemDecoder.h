//
// Created by Alexei Gladkikh on 18/09/16.
//

#ifndef MSP430EMU_SYSTEMDECODER_H
#define MSP430EMU_SYSTEMDECODER_H

#include "../../base/interfaces/IDecoder.h"

namespace dummy {
    class SystemDecoder : public vmc::IDecoder {
    public:
        vmc::PAInstruction decode(uint32_t data) override {
            throw exc::UnimplementedException();
        }
    };
}

#endif //MSP430EMU_SYSTEMDECODER_H
