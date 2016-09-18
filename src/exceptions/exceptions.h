//
// Created by Alexei Gladkikh on 15/09/16.
//

#include <exception>

#ifndef MSP430EMU_EXCEPTIONS_H
#define MSP430EMU_EXCEPTIONS_H

namespace exc {
    class MemoryUnavailable : public std::exception {

    };
}

#endif //MSP430EMU_EXCEPTIONS_H
