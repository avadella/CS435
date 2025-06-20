// IP Network Calculator: ip.cpp - Vadella and Baker
#include "ip.h"
#include <sstream>
#include <iostream>
#include <vector>

ipv4::ipv4() {}

ipv4::ipv4(std::string addr) { address_ = ipv4_to_uint(addr); }

ipv4::ipv4(uint32_t addr) { address_ = addr; }

uint32_t ipv4::ipv4_to_uint(std::string addr)
{
    //addr = 192.168.11.16
    uint32_t ip;
    std::string addr_copy = addr;
    std::vector<std::string> vectorOctets;
    for(int i = 0; i < 4; i++)
    {
        size_t separation = addr_copy.find('.');
        if (separation != std::string::npos) 
        {
            vectorOctets.push_back(addr_copy.substr(0, separation));
            addr_copy = addr_copy.substr(separation + 1);
        }
        else
        {
            vectorOctets.push_back(addr_copy);
        }
        ip = ip << 8;
        ip += stoi(vectorOctets[i]);
    }
    return ip;
}

std::string ipv4::uint_to_ipv4(uint32_t addr)
{
    std::string address = "";
    
    for (int i = 3; i >= 0; i--)
    {
        uint32_t octet = (addr >> (i * 8))  & 0xFF; 

        if (i < 3)
        {
            address += ".";
        }

        address += std::to_string(octet);

    }

    return address;

}

uint32_t ipv4::get() { return address_; }