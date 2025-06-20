// IP Forwarding: iface.cpp - Vadella and Baker
#include "iface.h"

iface::iface(int id, cidr const& net) : interfaceNumber_(id), net_(net), packetCount_(0) {}

int iface::get_interface_num()
{
    return interfaceNumber_;
}

cidr& iface::get_network()
{
    return net_;
}

int iface::get_packet_count()
{
    return packetCount_;
}

void iface::increment_packet_count()
{
    packetCount_++;
}

bool iface::operator<(iface& interface) 
{
    //return net_.get_netmaskLength() < interface.get_network().get_netmaskLength();
    return net_.get_netmaskLength() > interface.get_network().get_netmaskLength();          // change to be in descending order instead of ascending order
}