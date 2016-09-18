//
// Created by Alexei Gladkikh on 15/09/16.
//

#ifndef MSP430EMU_IDEBUGGABLE_H
#define MSP430EMU_IDEBUGGABLE_H

#include <stdint.h>
#include <list>
#include <vector>
#include "Breakpoints.h"

class IDebuggable {
//        val lock: ReentrantLock
//        val stopped: Condition
public:
    virtual uint8_t haltReason() = 0;
    virtual bool isRunning() = 0;
    virtual void halt() = 0;
    virtual void kill() = 0;
    virtual std::vector<uint8_t> readMemory(uint32_t vAddr, int count) = 0;
    virtual bool setBreakpoint(bpt::Type bpType, uint32_t vAddr, uint8_t count) = 0;
    virtual bool clearBreakpoint(bpt::Type bpType, uint32_t vAddr, uint8_t count) = 0;
    virtual void run() = 0;
    virtual bool step() = 0;
    virtual void terminate() = 0;
    virtual std::list<uint32_t> readRegisters() = 0;
    virtual uint32_t readRegister(int index) = 0;
    virtual bool writeRegister(int index, uint32_t value) = 0;
};


typedef std::shared_ptr<IDebuggable> PIDebuggable;


#endif //MSP430EMU_IDEBUGGABLE_H
