# IP Network Calculator
## Project Description
IP addresses and IP subnets are critical to network layer forwarding and routing functions.

To better understand how IP addresses are divided into subnets, you will write an IP network calculator. This assignment will explore the how the netmask determines subnet boundaries.

Your calculator will accept as input a CIDR format IP address and network mask as input, e.g. 192.168.0.0/24.

Your program will compute and display the following:
- Network address of the subnet
- Broadcast address of the subnet
- Number of usable, non-reserved addresses in the subnet

The program should then offer the option to display all usable addresses, one per line, in the subnet. 

IP addresses **must** be computed as integers and not manipulated as strings.

**We'll review this code in class but it will be a good starting point and includes tests.  When the tests all pass, it works.**

## Project Approach
Create a well-organized project developed using at least two (2) c++ classes, and ipv4 class and a cidr class.

Part 1. Create an IPv4 address class
- Create an IP address class which will include methods to:
    - Convert from dotted-quad format (string) to unsigned int: ipv4_to_uint
    - Convert from unsigned int to dotted-quad format (string): uint_to_ipv4

Part 2. Create a CIDR network class
- Convert a netmask (string), e.g. "19" to an unsigned int which is 19 ones, followed by 13 zeros, not decimal value 19
- Compute the network and broadcast addresses for a CIDR network from the ip address and netmask
- Compute the number of usable hosts addresses in the network

Part 3. Network Calculator
- Interact with the user to enter a CIDR format address
    - Create an instance of your CIDR object and print the network, broadcast and number of usable host addresses
    - Offer to print all the addresses in the network
        - print all IP addresses in the subnet in a loop, one per line

#### Testing: 
Tests are provided for IP and CIDR classes using libgtest.

## Project Requirements
- Written C++ , compiles and runs on thomas.butler.edu
- Must use your own IP and CIDR classes and not existing, system structs or classes
- Must list the subnet details and offer an option to view all addresses in the network
- Must prompt the user for the CIDR address or allow command line input (or both)