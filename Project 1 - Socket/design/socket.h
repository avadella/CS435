//Partial Implementation of Socket Class Header - Vadella

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

#ifndef SOCKET_H
#define SOCKET_H

using namespace std;

class socket 
{
    public: 
		socket();                   	//default constructor
		~socket();                  	//default destructor

		void createSocket();			//method for creating new socket variable 
		void socketConnect();			//method that allows client to connect to a server
		void socketClose();				//method for closing a socket 

	private: 
	struct sockaddr_in socketInfo; 		//found on http://www.yolinux.com/TUTORIALS/Sockets.html, https://book.systemsapproach.org/foundation/software.html#socket-api, and https://github.butler.edu/npartenh/cs435/tree/main/sockets/c%2B%2B
	std::string host = "localhost"; 	//something like this, found on https://github.butler.edu/npartenh/cs435/blob/main/sockets/c%2B%2B/client.cpp
};

#endif