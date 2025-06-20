#include <iostream>
#include "RDT.h"

int main(int argc, char* argv[])
{
    RDT rdt("127.0.0.1", 5432);                // need a host name/ip address and port 

    std::string msg = "Hello world";           // can hardcode, ask user for input (command line), etc.
    rdt.rdt_send(msg);

    return EXIT_SUCCESS;
}