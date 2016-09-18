//
// Created by Alexei Gladkikh on 18/09/16.
//

#ifndef MSP430EMU_RESPONSE_H
#define MSP430EMU_RESPONSE_H

#include <stdint.h>
#include <string>
#include <sstream>
#include <vector>
#include <list>

namespace gdb {
    class Message {
    private:
        std::string _data;
        bool _isRaw;

        std::string crc();
    public:
        Message(std::string data, bool isRaw = false) : _data(data), _isRaw(isRaw) { }
        const std::string data() {
            return _data;
        }
        std::string build();
        bool cksum(std::string crc);
        static Message interrupt(uint8_t interrupt);
        static Message ok();
        static Message empty();
        static Message error(uint8_t error);
        static Message dword(uint32_t value);
        static Message dwords(std::list<uint32_t> values);
        static Message bytes(std::vector<uint8_t> data);
        static Message raw(std::string message);
    };
}

#endif //MSP430EMU_RESPONSE_H
