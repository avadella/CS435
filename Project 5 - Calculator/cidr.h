// IP Network Calculator: cidr.h - Vadella and Baker
#ifndef CIDR_H
#define CIDR_H

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "ip.h"                         // conversion from dotted-quad string to uint32_t and back exist here

class cidr
{
    uint32_t address_;                  // user supplied
    uint32_t netmask_;                  // computed netmask
    uint32_t netaddr_;                  // computed network address
    uint32_t bcast_;                    // computed broadcast address

    public:
        cidr();
        cidr(std::string addr);
        std::string to_string();
        uint32_t get_network();
        uint32_t get_bcast();
        uint32_t nm_to_uint(int mask_length);
        int uint_to_nm(uint32_t mask);
        int contains(uint32_t addr);    // return -1 when false, nm length when true

        void printDetails();
        void listAddresses();
};

#endif