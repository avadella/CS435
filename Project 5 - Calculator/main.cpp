// IP Network Calculator: main.cpp - Vadella and Baker
#include <iostream>
#include "cidr.h"
#include "ip.h"

// to run: make, main or make test, ./test

int main(int argc, char* argv[])
{
    std::string net;
    char userInput;
    
    if(argc == 2) {
        net = argv[1];
    }
    else {
        std::cout << "Enter a CIDR format address: ";
        std::cin >> net;
    }
    
    cidr c(net);                                                    // create a cidr object

    std::cout << "Details for " << net << std::endl;
    c.printDetails();                                               // print network address, broadcast address, usable host IPs

    // offer to print all the addresses in the network in a loop
    std::cout << "View all the addresses in the network? (Y or N): ";
    std::cin >> userInput;

    if(userInput == 'y' || userInput == 'Y')
    {
        c.listAddresses();
    }
    else if(userInput == 'n' || userInput == 'N')
    {
        return EXIT_SUCCESS;
    }
    else
    {
        std::cout << "ERROR: Invalid Input. Please enter Y or N." << std::endl;
    }

    return EXIT_SUCCESS;
}