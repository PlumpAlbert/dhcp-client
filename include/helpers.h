//
// Created by plump on 1/3/20.
//

#ifndef DHCP_CLIENT_HELPERS_H
#define DHCP_CLIENT_HELPERS_H
#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

/**
 * Returns MAC address of the adapter_name
 * @param adapter_name The name of the network adapter
 */
const char *get_mac_address(const char *adapter_name);
#endif // DHCP_CLIENT_HELPERS_H
