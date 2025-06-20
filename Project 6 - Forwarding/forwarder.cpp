// IP Forwarding: forwarder.cpp - Vadella and Baker
#include "forwarder.h"

forwarder::forwarder() {}   

forwarder::~forwarder()
{
    for(iface * i: forwardingTable)
    {
        delete i;
    }
}

void forwarder::add_interface(iface * interface)
{
    forwardingTable.push_back(interface);
}                                 

void forwarder::forward(const std::string& destinationIP)
{
    iface* bestMatch = find_longest_match(destinationIP);

    if (bestMatch != nullptr)
    {
        bestMatch->increment_packet_count();
    }
    else
    {
        // no match found — fall back to default route (0.0.0.0/0)
        for (iface* i : forwardingTable)
        {
            if (i->get_network().get_netmaskLength() == 0) // default route
            {
                i->increment_packet_count();
                break;
            }
        }
    }
}        

iface * forwarder::find_longest_match(const std::string& destinationIP)
{
    uint32_t dest = ipv4::ipv4_to_uint(destinationIP);
    iface * bestMatch = nullptr;
    int longestMask = -1;

    for (iface * i : forwardingTable)
    {
        int maskLength = i->get_network().contains(dest);       // returns -1 if not in range

        if (maskLength > longestMask)
        {
            longestMask = maskLength;
            bestMatch = i;
        }
    }

    return bestMatch;                                           // returns nullptr if no match found
}

void forwarder::sort_table()
{
    std::sort(forwardingTable.begin(), forwardingTable.end());
} 

void forwarder::print()
{
    /*for(int i = 0; i < 8; i++)
    {
        std::cout << forwardingTable[i]->get_interface_num() << ":\t" << forwardingTable[i]->get_packet_count() << std::endl;
    } -- this assumes that forwardingTable[0] is interface 0, but sort_table() which sorts forwarding table by subnet mask, not by interface num */ 
    
    // copy and sort by interface number
    std::vector<iface*> sorted = forwardingTable;
    std::sort(sorted.begin(), sorted.end(), [](iface* a, iface* b) {
        return a->get_interface_num() < b->get_interface_num();
    });

    for (iface* i : sorted)
    {
        std::cout << i->get_interface_num() << ":\t" << i->get_packet_count() << std::endl;
    }
}