cmake_minimum_required(VERSION 3.5)
project(msp430emu)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/gdbstub/Message.cpp
        src/gdbstub/Processor.cpp
        src/gdbstub/ClientThread.cpp
        src/gdbstub/Server.cpp
        src/main.cpp)
add_executable(msp430emu ${SOURCE_FILES})