#include "RDT.h"

unit32_t RDT::compute_checksum(std::string msg)
{
    // compute and return crc32 of msg.c_str();
    return 0;
}

void RDT::rdt_send(std::string msg)
{
    Packet p(msg);                                              // to send message, need a packet 
    unit32_t csum = compute_checksum(msg);                      // note: csum is a "short hand" for checksum
    p.set_checksum(csum);

    p.set_sequence(sequence_);                                  // setting sequence number

    bool acked = false;
    int dl = 128;                                               // data length

    while(!acked)
    {
        udt_send(p.pack());                                      // turn into byte array that can be sent, and then use udt_send to send it

        unsigned char* data = (char*)malloc(dl);
        int bytes_received = socket_.recvfrom(data, data_len);   // receive response

        if_ack(data) 
        { 
            sequence_ = !sequence_;                              // change 0-->1 or 1-->0 
            acked = true; 
        }
        // need to receive ACK or NAK -- use a while loop ("good control structure for sending something many times")
        /*if(NAK) { // retry }
        else { break; }
        */
    }
}

bool RDT::if_ack(data)
{
    if(csum is okay && sequence is expected/"in-order")       
        return true;
        
    return false;
}

void RDT::rdt_rcv()
{

}

void udt_send(unsigned char* data, int data_len)
{
    int bytes_sent = socket_.sendto(socket_, data, data_len, dst.addr, dst.port);
    return bytes_sent;
}