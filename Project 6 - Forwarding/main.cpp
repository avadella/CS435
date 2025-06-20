// IP Forwarding: main.cpp - Vadella and Baker
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "cidr.h"
#include "ip.h"
#include "iface.h"
#include "forwarder.h"

int main()
{
    forwarder f;
    std::string cidr_adr[7] = {
        "192.168.1.0/28", "192.168.1.0/24", "10.0.1.0/24",
        "10.0.2.0/23", "10.0.0.0/21", "172.16.0.0/20", "159.242.0.0/16"
    };

    // regular interfaces
    for (int i = 0; i < 7; i++)
    {
        cidr c(cidr_adr[i]);
        iface * interface = new iface(i,c);
        f.add_interface(interface);
    }

    cidr defaultRoute("0.0.0.0/0");
    iface * defaultFace = new iface(7, defaultRoute);
    
    f.add_interface(defaultFace);

    f.sort_table();

    std::fstream file("destinations.txt");
    std::string adr;
    while (getline(file, adr))
    {
        f.forward(adr);
    }

    f.print();
    file.close();

    return EXIT_SUCCESS;
}