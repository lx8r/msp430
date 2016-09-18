//
// Created by Alexei Gladkikh on 15/09/16.
//

#ifndef MSP430EMU_BREAKPOINTS_H
#define MSP430EMU_BREAKPOINTS_H

namespace bpt {
    enum Type { SOFTWARE = 0, HARDWARE = 1, WRITE = 2, READ = 3, ACCESS = 4 };
}

#endif //MSP430EMU_BREAKPOINTS_H
