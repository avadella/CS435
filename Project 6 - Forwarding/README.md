# IP Forwarding
## Project Description


Routers perform two functions, one of which is forwarding, or selecting the best output interface for each datagram.

To select the best output interface, the router will find the interface using the longest matching prefix. This means that if there are multiple destination networks, or subnets, which match the destination IP address, choose the one with the longest network mask, or which matches the most bits.  In the case of a tie, or two equal length matches, either interface may be selected.  In this scenario, in practice, routers may prefer one or commonly round-robin.

Utilizing your IPv4 and CIDR objects from the previous assignment, create a forwarding table to simulate forwarding.

## Project Requirements


For this assignment you'll also want to create an iface class and a forwarder class.

1. The iface class (iface is shorthand for interface without appearing as a keyword) will contain the interface number, the cidr network to which it's connected and a count of forwarded packets (matches)

2. The forwarder class will maintain a forwarding table of iface objects.  It will have a method to forward, or select the right interface and increment the iface.count, and a method to report the iface counts to validate correct function.

You will most likely want to sort your forwarding table so that the iface objects which have cidr networks with the longest netmasks come first.  You may achieve this by sorting the objects or just pre-sorting your input.

## Example Data/Program Validation
For the Interfaces and CIDR networks below:

```
0: 192.168.1.0/28
1: 192.168.1.0/24
2: 10.0.1.0/24
3: 10.0.2.0/23
4: 10.0.0.0/21
5: 172.16.0.0/20
6: 159.242.0.0/16
7: default (anything that isn't already matched)
```
The destinations.txt data file should produce the counts:

```
0: 82
1: 1335
2: 1600
3: 1750
4: 919
5: 1430
6: 1466
7: 1418
```