#include <cstring>
#include <iostream>
#include <netdb.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

const bool DEBUG = true;
const int MAXHOSTNAME = 256;

int main(int argc, char **argv) {
  socklen_t peer_addrlen;
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  struct sockaddr_storage peer_addr;

  std::string host = "0.0.0.0";
  int s = -1; // our socket
  int port = 43500;

  if (argc == 2) {
    port = std::stoi(argv[1]);
  }

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;       /* Allow IPv4 or IPv6 */
  hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
  hints.ai_flags = 0;              /* For wildcard IP address */
  hints.ai_protocol = 0;           /* Any protocol */
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;

  s = getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &result);
  if (s != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    exit(EXIT_FAILURE);
  }

  /* getaddrinfo() returns a list of address structures.
     Try each address until we successfully bind(2).
     If socket(2) (or bind(2)) fails, we (close the socket
     and) try the next address. */

  for (rp = result; rp != NULL; rp = rp->ai_next) {
    s = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (s == -1)
      continue;

    if (bind(s, rp->ai_addr, rp->ai_addrlen) == 0)
      break; /* Success */

    close(s);
  }

  freeaddrinfo(result); /* No longer needed */

  if (rp == NULL) { /* No address succeeded */
    std::cerr << "Could not bind" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "Listening on " << host << ":" << port << std::endl;

  listen(s, 1);

  while (true) {
    int clientSocket = accept(s, NULL, NULL);
    if (clientSocket < 0) {
      perror("accept");
      close(s);
      exit(EXIT_FAILURE);
    }

    if(DEBUG)
        std::cout << "connection accepted" << std::endl;

    ssize_t rc = 0; // Actual number of bytes read
    char buf[512];

    // rc is the number of characters returned.

    rc = recv(clientSocket, buf, 512, 0);

    if(DEBUG)
        std::cout << "received " << rc << " bytes" << std::endl;

    // send it back!
    ssize_t sent = send(clientSocket, buf, rc, 0);
    if (sent < 0) {
      // throw std::runtime_error(strerror(errno));  // NOLINT bugprone-exception-escape
      perror("send");
      close(clientSocket);
      exit(EXIT_FAILURE);
    }

    if(DEBUG)
        std::cout << "sent " << sent << " bytes" << std::endl;

    close(clientSocket);
  }

  close(s);
  return 0;
}