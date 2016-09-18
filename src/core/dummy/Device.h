//
// Created by Alexei Gladkikh on 18/09/16.
//

#ifndef MSP430EMU_DEVICE_H
#define MSP430EMU_DEVICE_H

#include "../base/interfaces/IDebuggable.h"
#include "../base/interfaces/ADevice.h"
#include "../base/Breakpoints.h"
#include "hardware/CPU.h"
#include "hardware/SystemMemory.h"
#include "hardware/SystemDecoder.h"
#include "hardware/SystemTimer.h"

namespace dummy {
    class Device : public vmc::ADevice, public IDebuggable {
    public:
        Device() {
            cpu = std::make_shared<CPU>();
            memory = std::make_shared<SystemMemory>();
            decoder = std::make_shared<SystemDecoder>();
            timer = std::make_shared<SystemTimer>();
        }

        uint8_t haltReason() override {
            return 0x05;
        }

        bool isRunning() override {
            return false;
        }

        void halt() {}
        void kill() {}

        std::vector <uint8_t> readMemory(uint32_t vAddr, int count) {
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

        std::list <uint32_t> readRegisters() override {
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
#endif //MSP430EMU_DEVICE_H
