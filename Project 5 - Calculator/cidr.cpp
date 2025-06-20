// IP Network Calculator: cidr.cpp - Vadella and Baker
#include "cidr.h"
#include "ip.h"
#include <cmath>
#include <vector>

cidr::cidr(): address_(0), netmask_(0), netaddr_(0), bcast_(0) {}

cidr::cidr(std::string addr)
{
    // split the addr parameter into the dotted quad portion and the netmask length
    size_t position = addr.find('/');
    std::string address = addr.substr(0, position);
    std::string netmask = addr.substr(position + 1);

    // these will work to get started but should be dynamic / user input
    // std::string address = "10.0.0.0";
    // std::string netmask = "24";
    address_ = ipv4::ipv4_to_uint(address);
    netmask_ = nm_to_uint(std::stoi(netmask));


    // compute broadcast and network address
    bcast_ = address_ | ~netmask_;                                                             // compute with address_ and netmask_
    netaddr_ = address_ & netmask_;                                                            // compute with address_ and netmask_
}

std::string cidr::to_string() { return ipv4::uint_to_ipv4(address_); }

uint32_t cidr::get_network() { return netaddr_; }

uint32_t cidr::get_bcast() { return bcast_; }

uint32_t cidr::nm_to_uint(int mask_length)
{
    unsigned int nm = (0xFFFFFFFF << (32 - mask_length)) & 0xFFFFFFFF;
    return nm;
}

int cidr::uint_to_nm(uint32_t mask)
{
    int mask_length = 0;

    // compute the mask length
    while(mask) 
    {
        mask_length += mask & 1;
        mask >>= 1;                                 // shift mask to the right
    }

    return mask_length;
}

int cidr::contains(uint32_t addr)
{
    // return the cidr mask length if address in network
    if (addr >= netaddr_ && addr <= bcast_)
    {
        return uint_to_nm(netmask_);
    }

    // return -1 if address not in network
    return -1;
}

void cidr::printDetails() 
{
    // broadcast
    // bcast_ = address_ | ~netmask_;
    std::string DQbcast = ipv4::uint_to_ipv4(bcast_);
    std::cout << "Broadcast address: " + DQbcast << std::endl;

    // network 
    // netaddr_ = address_ & netmask_;
    std::string DQnetadrr = ipv4::uint_to_ipv4(netaddr_);
    std::cout << "Network address: " + DQnetadrr << std::endl;

    // calculate netmask_length
    int netmask_length = uint_to_nm(netmask_);

    // numHosts
    int power = 32 - netmask_length;
    int numHosts_ = (pow(2, power)) - 2;
    std::cout << "Number of usable hosts addresses in the network: ";
    std::cout << numHosts_ << std::endl;
}

void cidr::listAddresses()
{
    for(int i = 1; i < (bcast_ -  netaddr_); i++)
    {
        std::cout << ipv4::uint_to_ipv4(netaddr_ + i) << std::endl;
    }
}