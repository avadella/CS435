// Write an HTTP Message Object: socket.cpp - Vadella
// Testing notes: make test, ./test

#include "socket.h"

Socket::Socket() : host_(DEFAULT_HOST), port_(DEFAULT_PORT) {}
Socket::Socket(std::string host, int port) : host_(host), port_(port) {}
Socket::Socket(int socket) : socket_(socket) {}

Socket::~Socket() { ::close(socket_); }

void Socket::connect()
{
    // Get system information
    struct addrinfo hints, *servinfo, *p;
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;                                                            // any protocol

    // getaddrinfo looks up the remote system info
    if ((rv = getaddrinfo((char *)host_.c_str(), std::to_string(port_).c_str(),
                            &hints, &servinfo)) != 0) {
        std::cerr << "getaddrinfo: " << gai_strerror(rv) << std::endl;
        throw std::runtime_error(gai_strerror(rv));
        exit(1);
    }

    // loop through all the results and connect to the first one we can
    // alternately use the first result
    for (p = servinfo; p != NULL; p = p->ai_next) {

        // create socket
        if ((socket_ = ::socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
        throw std::runtime_error(strerror(errno));
        continue;
        }

        // connect
        if (::connect(socket_, p->ai_addr, p->ai_addrlen) == -1) {
        throw std::runtime_error(strerror(errno));
        ::close(socket_);
        continue;
        }

        break;                                                                        // if we get here, we must have connected successfully
    }

    if (p == NULL) {
        // looped off the end of the list with no connection
        std::cerr << "failed to connect" << std::endl;
        exit(2);
    }

    freeaddrinfo(servinfo);
}

ssize_t Socket::send(const unsigned char *message, int message_length)
{
    ssize_t sent = 0;

    if ((sent = ::send(socket_, message, message_length, 0)) < 0) {
        throw std::runtime_error(strerror(errno));
        ::close(socket_);
        exit(EXIT_FAILURE);
    }

    return sent;
}

ssize_t Socket::recv(unsigned char *buf)
{
  int rc = 0;                                                                         // Actual number of bytes read
  //char buf[512];

  // rc is the number of characters returned

  rc = ::recv(socket_, buf, 512, 0);
  buf[rc] = (char)NULL;                                                               // c-strings are null terminated

  //std::cout << "Number of bytes read: " << rc << std::endl;
  //std::cout << "Received: " << buf << std::endl;

  return rc;
}

//bind() and listen() methods combined into the listen() function!!!
void Socket::listen(void)
{
    struct sockaddr_in socketInfo;

    if (::bind(socket_, (struct sockaddr *)&socketInfo, sizeof(socketInfo)) < 0) {
        ::close(socket_);
        perror("bind");
        exit(EXIT_FAILURE);
    }

  ::listen(socket_, 1);
}

int Socket::accept(void)
{
  int socketConnection;
  if ((socketConnection = ::accept(socket_, NULL, NULL)) < 0) {
    perror("accept");
    ::close(socket_);
    exit(EXIT_FAILURE);
  }

  return socketConnection;
}

void Socket::close(void)
{
  ::close(socket_); //when we want standard namespace close, need to prefix with :: b/c need to differentiate between socket close and std::close
}