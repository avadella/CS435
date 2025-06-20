// Write an HTTP Message Object: main.cpp - Vadella
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "socket.h"
#include "request.h"
#include "response.h"

const std::string host = "httpbin.org";
const bool DEBUG = true;
const int port = 80;
const int buffer_size = 2048; 

int main() 
{
    unsigned char buf[buffer_size];
    int sent, received = 0;

    Socket s(host, port);
    s.connect();

    request request;
    response response;
    std::string getMessage;
    std::string headMessage;
    std::string postMessage;

    // Testing GET
    request.set_method("GET");
    request.set_path("get");
    request.add_header("Host", host);

    getMessage = request.marshal();

    sent = s.send(reinterpret_cast<const unsigned char*>(getMessage.c_str()), getMessage.length());
    received = s.recv(reinterpret_cast<unsigned char*>(buf));

    //request.to_string();                                                                                // prints request in format from class
    std::cout << "Data from unmarshaling:   " <<response.unmarshal(buf) << std::endl;
    //response.to_string();
    memset(buf, 0, sizeof(buf)); 

    
    // Testing HEAD
    request.set_method("HEAD");
    request.set_path(""); 

    headMessage = request.marshal();

    sent = s.send(reinterpret_cast<const unsigned char*>(headMessage.c_str()), headMessage.length());
    received = s.recv(reinterpret_cast<unsigned char*>(buf));

    //request.to_string();
    std::cout << "Data from unmarshaling:   " << response.unmarshal(buf) << std::endl;
    //response.to_string();
    memset(buf, 0, sizeof(buf)); 


    // Testing POST
    std::string data = "name=Anna&is=diva";
    request.set_method("POST");
    request.set_path("post");
    request.add_header("Content-Type", "application/json");
    request.add_header("Content-Length", std::to_string(data.length()));

    postMessage = request.marshal();
    postMessage = postMessage + data;

    sent = s.send(reinterpret_cast<const unsigned char*>(postMessage.c_str()), postMessage.length());
    received = s.recv(reinterpret_cast<unsigned char*>(buf));

    //request.to_string();
    std::cout << "Data from unmarshaling:   " << response.unmarshal(buf) << std::endl;
    //response.to_string();
    memset(buf, 0, sizeof(buf)); 

    return 0;
}