//
// Created by Alexei Gladkikh on 18/09/16.
//

#include <iomanip>
#include <sstream>
#include "Message.h"
#include "../helpers/helpers.h"

#define log el::Loggers::getLogger("gdbMessage")

std::string gdb::Message::crc() {
    uint8_t crcVal = 0;
    for (int i = 0; i < _data.length(); i++)
        crcVal += _data[i];
    return helpers::sformat("%02x", crcVal);
}

std::string gdb::Message::build() {
    if (!_isRaw) {
        std::ostringstream ss;
        ss << "$";
        ss << this->_data;
        ss << "#";
        ss << crc();
        return ss.str();
    } else {
        return std::string(this->_data);
    }
}

bool gdb::Message::cksum(std::string crc) {
    return this->crc() == crc;
}

gdb::Message gdb::Message::interrupt(uint8_t interrupt) {
    std::string msg = helpers::sformat("T%02x", interrupt);
    return Message(msg);
}

gdb::Message gdb::Message::ok() {
    return Message("OK");
}

gdb::Message gdb::Message::empty() {
    return Message("");
}

gdb::Message gdb::Message::error(uint8_t error) {
    std::string msg = helpers::sformat("E%02x", error);
    return Message(msg);
}

gdb::Message gdb::Message::dword(uint32_t value) {
    std::ostringstream response;
    response << std::setfill('0') << std::setw(8) << std::hex << htonl(value);
    return Message(response.str());
}

gdb::Message gdb::Message::dwords(std::list<uint32_t> values) {
    std::ostringstream response;
    for (auto value : values)
        response << std::setfill('0') << std::setw(8) << std::hex << htonl(value);
    return Message(response.str());
}

gdb::Message gdb::Message::bytes(std::vector<uint8_t> data) {
    std::ostringstream response;
    for (auto byte : data)
        response << std::setfill('0') << std::setw(2) << std::hex << byte;
    return Message(response.str());
}

gdb::Message gdb::Message::raw(std::string message) {
    return Message(message, true);
}