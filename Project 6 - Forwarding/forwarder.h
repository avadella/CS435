// IP Forwarding: forwarder.h - Vadella and Baker
#ifndef FORWARDER_H
#define FORWARDER_H

#include "iface.h"
#include "cidr.h"
#include "ip.h"

#include <vector>

class forwarder
{
    private: 
        std::vector<iface *> forwardingTable;                           // list of interfaces in forwarding table
    
    public: 
        forwarder();                                                    // constructor
        ~forwarder();                                                  
        void add_interface(iface * interface);                          // method to add new interface to forwarding table

        void forward(const std::string& destinationIP);                 // method for forwarding based on longest matching prefix
        iface * find_longest_match(const std::string& destinationIP);   // method for finding best matching interface based on longest prefix match
        void sort_table();                                              // method for sorting forwarding table by longest netmask length
        void print();
};

#endif