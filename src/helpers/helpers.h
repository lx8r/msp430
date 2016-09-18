//
// Created by Alexei Gladkikh on 15/09/16.
//

#ifndef MSP430EMU_HELPERS_H_H
#define MSP430EMU_HELPERS_H_H

#include <vector>
#include <string>
#include <sstream>
#include <thread>

namespace helpers {
    class ARunnableThread : public std::thread {
    public:
        virtual void run() = 0;

        ARunnableThread() : std::thread([this] { this->run(); }) { }
    };

    inline std::vector<std::string> split(const std::string &s, char delim) {
        std::stringstream ss;
        ss.str(s);
        std::string item;
        std::vector<std::string> result;
        while (getline(ss, item, delim))
            result.push_back(item);
        return result;
    }

    // http://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
    inline std::string sformat(const std::string fmt_str, ...) {
        int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
        std::string str;
        std::unique_ptr<char[]> formatted;
        va_list ap;
        while(1) {
            formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
            strcpy(&formatted[0], fmt_str.c_str());
            va_start(ap, fmt_str);
            final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
            va_end(ap);
            if (final_n < 0 || final_n >= n)
                n += abs(final_n - n + 1);
            else
                break;
        }
        return std::string(formatted.get());
    }
}

#endif //MSP430EMU_HELPERS_H_H
