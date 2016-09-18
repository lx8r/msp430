//
// Created by Alexei Gladkikh on 18/09/16.
//

#ifndef MSP430EMU_IMEMORY_H
#define MSP430EMU_IMEMORY_H

#include <cstdint>
#include <vector>

namespace vmc {
    class IMemory {
    public:
        virtual void blockWrite(uint32_t vAddr, std::vector<uint8_t> bytes) = 0;
        virtual std::vector<uint8_t> blockWrite(uint32_t vAddr) = 0;

        virtual uint32_t loadByte(uint32_t vAddr) = 0;
        virtual uint32_t loadWord(uint32_t vAddr) = 0;
        virtual uint32_t loadDword(uint32_t vAddr) = 0;

        virtual void storeByte(uint32_t vAddr, uint32_t data) = 0;
        virtual void storeWord(uint32_t vAddr, uint32_t data) = 0;
        virtual void storeDword(uint32_t vAddr, uint32_t data) = 0;
    };

    typedef std::shared_ptr<IMemory> PIMemory;
}

#endif //MSP430EMU_IMEMORY_H
