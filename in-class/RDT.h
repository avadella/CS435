#ifndef RDT_H
#define RDT_H

#include <iostream>
#include "zlib.h"       // and compile it with -lz
#include "cs435.h"      // if working on thomas, should be included and has UDP support

// what does a packet look like? -- could be a struct 
/*struct packet {
    char* data;         // minimum packet is data, do not want to use std::string b/c data is a byte stream whereas a std::string is an object (which might confuse reciever)
};*/

// could also make a class for packet 
class Packet {
    std::string data_;                      // assuming that we are sending standard txt messages for the purposes of this example
    unit32_t checksum_;
    int sequence_;                          // sequence number, will only be 0 or 1

    public: 
        Packet();
        Packet(std::string data);           // make_pkt
        pack();                             // deliver_data
        unpack(unsigned char* data);
        set_checksum(uint32_t csum);
        set_sequence(int seq);              // to ack 0 or 1 in the packet
}

class RDT
{
    Socket socket_;
    int sequence_;                                      // are we on 0 or 1 next? -- "keeping track of where we are, did we just send zero or one?"

    public:
        unit32_t compute_checksum(std::string msg);     // the csum actually is part of the packet data (once it is computed -- could make the packet constructor compute it instead)
        rdt();
        rdt(std::string host, int port);                // make constructor that takes host name and port as input -- "go ahead and create a socket"
        rdt_send(std::string msg);
        rdt_rcv();
        udt_send();
};

#endif