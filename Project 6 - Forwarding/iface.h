// IP Forwarding: iface.h - Vadella and Baker
#ifndef IFACE_H
#define IFACE_H

#include "cidr.h"

class iface
{
    private: 
        int interfaceNumber_;                                     // interface number
        cidr net_;                                                // CIDR network
        int packetCount_;                                         // count of forwarded packets

    public: 
        iface(int interfaceNumber,  const cidr& net);             // constructor -- initialize iface w/ number and associated CIDR network

        // getters
        int get_interface_num();
        cidr& get_network();
        int get_packet_count();

        void increment_packet_count();                            // increment the forwarded packet count
        bool operator<(iface& interface) ;
};

#endif