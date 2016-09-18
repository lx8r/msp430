//
// Created by Alexei Gladkikh on 18/09/16.
//

#ifndef MSP430EMU_DUMMY_H
#define MSP430EMU_DUMMY_H

#include "../interfaces/IDebuggable.h"

namespace targets {
    class Dummy : public IDebuggable {
        uint8_t haltReason() override {
            return 0x05;
        }

        bool isRunning() override {
            return false;
        }

        void halt() { }
        void kill() { }

        std::vector<uint8_t> readMemory(uint32_t vAddr, int count) {
            return std::vector<uint8_t>();
        }

        bool setBreakpoint(bpt::Type bpType, uint32_t vAddr, uint8_t count) override {
            return true;
        }

        bool clearBreakpoint(bpt::Type bpType, uint32_t vAddr, uint8_t count) override {
            return true;
        }

        void run() override {

        }

        bool step() override {
            return true;
        }

        void terminate() override {

        }

        std::list<uint32_t> readRegisters() override {
            return std::list<uint32_t>();
        }

        uint32_t readRegister(int index) override {
            return 0xDEADBEEF;
        }

        bool writeRegister(int index, uint32_t value) override {
            return true;
        }
    };
}

#endif //MSP430EMU_DUMMY_H
