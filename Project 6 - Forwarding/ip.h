// IP Forwarding: ip.h - Vadella and Baker
#ifndef IP_H
#define IP_H

#include <algorithm>
#include <cstdint>
#include <sstream>
#include <string>

class ipv4
{
    uint32_t address_;

    public:
        ipv4();
        ipv4(std::string addr);
        ipv4(uint32_t addr);
        static uint32_t ipv4_to_uint(std::string addr);                 // convert from dotted-quad format (string) to unsigned int
        static std::string uint_to_ipv4(uint32_t addr);                 // convert from unsigned into to dotted-quad format (string)
        uint32_t get();
};

#endif