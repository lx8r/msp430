//
// Created by Alexei Gladkikh on 18/09/16.
//

#ifndef MSP430EMU_SYSTEMMEMORY_H
#define MSP430EMU_SYSTEMMEMORY_H

#include <cstdint>
#include <vector>
#include "../../base/interfaces/IMemory.h"
#include "../../base/exceptions/exceptions.h"

namespace dummy {
    class SystemMemory : public vmc::IMemory {
    private:
        std::vector<uint8_t> _data;
    public:
        SystemMemory() {
            _data = std::vector<uint8_t>(1024);
        }

        void blockWrite(uint32_t vAddr, std::vector<uint8_t> bytes) override {
            throw exc::UnimplementedException();
        }

        std::vector<uint8_t> blockWrite(uint32_t vAddr) override {
            throw exc::UnimplementedException();
        }

        uint32_t loadByte(uint32_t vAddr) override {
            throw exc::UnimplementedException();
        }

        uint32_t loadWord(uint32_t vAddr) override {
            throw exc::UnimplementedException();
        }

        uint32_t loadDword(uint32_t vAddr) override {
            throw exc::UnimplementedException();
        }

        void storeByte(uint32_t vAddr, uint32_t data) override {
            throw exc::UnimplementedException();
        }

        void storeWord(uint32_t vAddr, uint32_t data) override {
            throw exc::UnimplementedException();
        }

        void storeDword(uint32_t vAddr, uint32_t data) override {
            throw exc::UnimplementedException();
        }
    };
}

#endif //MSP430EMU_SYSTEMMEMORY_H
