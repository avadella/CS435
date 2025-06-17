# Design a Socket Object
## Create an Object in C++ to Implement a Socket Class that Wraps the C-style Socket API
This is an object-oriented starting point for other assignments, and we will create some of the code together after reviewing ideas together.

## Socket Class Design
The Socket class should include or address how you will approach:
- organization
- a single class, a parent and child class (or classes), client and server classes
- semantics - do you reuse the standard verbs like listen, connect and send or name your member functions differently?
- how complicated is your object's API, i.e. how hard or straightforward is it to use?  Is it flexible, intuitive, complete?
- constructors for: servers, clients, accept()'ing client connections
- methods - how to organize the required steps for clients and servers which include: 
    - socket() - creating a new socket variable
    - connect() - client connects to a server
    - close() - closes a socket
    - bind() - servers bind a socket to a port
    - listen() - servers listen for connections on the bound port
    - accept() - servers accept new client connections
    - send() - send TCP data
    - recv() - receive TCP data
    - sendto() - send UDP data
    - recvfrom() - receive UDP data
- Plan, at a high level, to account for both TCP, or SOCK_STREAM and UDP, or SOCK_DGRAM sockets
- Plan, at a high level, for IPv4, or AF_INET only

## Socket Class Implementation Requirements
The Socket class should include:
- three constructors: default, host and port, socket 
- methods - how to organize the required steps for clients and servers which include:
    - connect() - client connects to a server
    - close() - closes a socket
    - bind() - servers bind a socket to a port
    - listen() - servers listen for connections on the bound port
    - accept() - servers accept new client connections
    - send() - send TCP data
    - recv() - receive TCP data
    - sendto() - send UDP data
    - recvfrom() - receive UDP data
- Account for both SOCK_STREAM and SOCK_DGRAM sockets
- Account for IPv4 or AF_INET only

## Resources
- Socket API from [Computer Networks: A Systems Approach](https://book.systemsapproach.org/foundation/software.html#socket-apiLinks)
- Sample programs in [cs435 github](https://github.butler.edu/npartenh/cs435/tree/main/sockets/c%2B%2B)
- Diagrams of typical client and server operation:
![socket-img](https://github.com/user-attachments/assets/f8037a0d-3a28-461d-b5cf-a5f0b25e590d)
![socket-img-2](https://github.com/user-attachments/assets/7c039be9-2951-4650-8af7-554fc2c821ef)
