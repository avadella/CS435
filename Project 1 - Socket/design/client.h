//Partial Implementation of Client Class Header - Vadella

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

#ifndef CLIENT_H
#define CLIENT_H

using namespace std;

class client
{
    public: 
		client();                   	                //default constructor
        //parameterized constructor
		~client();                  	                //default destructor

        void clientConnect();                           //method that allows client to connect to a server
        void sendto(string message);                    //method to send UDP data (sends a message to the server)
        void recvfrom();                                //method to receive UDP data

        void clientClose();

    private: 
        int socketHandle__;                             //found on http://www.yolinux.com/TUTORIALS/Sockets.html -- variable that holds reference to socket
        int portNumber__;                               //found on http://www.yolinux.com/TUTORIALS/Sockets.html
};

#endif