// Socket Object for Mail User Agent - Vadella
// Implementation of socket.h

#pragma once															// preprocessor to ensure header file is included only once in a single compilation

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

const int MAXHOSTNAME = 256;
const int DEFAULT_PORT = 43500;
const std::string DEFAULT_HOST = "127.0.0.1";							// local host address 
// const std::string DEFAULT_HOST = "thomas.butler.edu";

class Socket
{
  private:
	std::string host_;
	int port_;
	int socket_;
	struct addrinfo address_info;

  public:
	Socket();															// default constructor
	Socket(std::string host, int port);									// host and port constructor
	Socket(int socket);													// socket constructor
	~Socket();
	void connect(void);													// method for client to connect to a server
	void listen(void);													// method for allowing servers to bind a socket to a port and to listen for connection on bound port 
	int accept(void);													// method for allowing servers to accept new client connections
	ssize_t send(const unsigned char *message, int message_length);		// method for sending data
	ssize_t recv(unsigned char *buf);									// method for receiving data
	void close();														// method for closing a socket

	// ssize_t sendto(char* message, int message_length);
	// ssize_t recvfrom(void);
};