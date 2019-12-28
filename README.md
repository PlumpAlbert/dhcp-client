# DHCP Client (using UNIX sockets)

## Roadmap
1. Get MAC-address of the client :blush:
2. Send DHCP packet
    - create DHCP packet :worried:
    - encapsulate DHCP packet into UDP datagram :frowning:
    - encapsulate UDP datagram into IP packet :fearful:
    - encapsulate IP packet into Ethernet packet :cold_sweat:
3. wait for the DHCPOFFER :scream:
4. repeat step 2 for DHCPREQUEST :sob:
5. print received IP address and DHCP options 