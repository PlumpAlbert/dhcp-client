//
// Created by plump on 1/3/20.
//

#ifndef DHCP_CLIENT_HELPERS_H
#define DHCP_CLIENT_HELPERS_H
#include <arpa/inet.h>
#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include "dhcp.h"

/**
 * Returns MAC address of the adapter_name
 * @param adapter_name The name of the network adapter
 */
const char *get_mac_address(const char *adapter_name);

/*
 * Prints packet body to stdout
 */
void print_packet(dhcp_packet const *packet);
#endif // DHCP_CLIENT_HELPERS_H
