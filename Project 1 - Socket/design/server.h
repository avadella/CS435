//Partial Implementation of Server Class Header - Vadella

//found on http://www.yolinux.com/TUTORIALS/Sockets.html and https://github.butler.edu/npartenh/cs435/tree/main/sockets/c%2B%2B
#include <cerrno>
#include <cstdlib>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <string>
#include <iostream>

#define MAXHOSTNAME 256 				//found on http://www.yolinux.com/TUTORIALS/Sockets.html and https://github.butler.edu/npartenh/cs435/tree/main/sockets/c%2B%2B

#ifndef SERVER_H
#define SERVER_H

using namespace std;

class server 
{
    public: 
		server();                   	                //default constructor
        //parameterized constructor
		~server();                  	                //default destructor

        void bind();                                    //method for binding a socket to a port
        void listen();                                  //method that allows server to listen for connections on the bound port
        void accept(int connection);                    //method that allows servers to accept new client connections

        void send(string message);                      //method that sends TCP (Transmission Control Protocol) data
        void recv(int connection);                      //method that recieves TCP data

        void serverClose(int socketHandle);			    //found on https://github.butler.edu/npartenh/cs435/tree/main/sockets/c%2B%2B          

    private: 
        int socketHandle__;                             //found on http://www.yolinux.com/TUTORIALS/Sockets.html -- variable that holds reference to socket
        int portNumber__;                               //found on http://www.yolinux.com/TUTORIALS/Sockets.html and https://github.butler.edu/npartenh/cs435/tree/main/sockets/c%2B%2B
};

#endif