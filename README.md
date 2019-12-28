# DHCP Client (using UNIX sockets)

## Roadmap
1. Get MAC-address of the client :blush:
2. Send DHCP packet
    - create DHCP packet :relaxed:
    - encapsulate DHCP packet into UDP datagram :worried:
    - encapsulate UDP datagram into IP packet :frowning:
    - encapsulate IP packet into Ethernet packet :fearful:
3. wait for the DHCPOFFER :relieved:
4. repeat step 2 for DHCPREQUEST :cold_sweat:
5. print received IP address and DHCP options