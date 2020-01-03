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
#include "dhcp_option.h"

/**
 * Returns MAC address of the adapter_name
 * @param adapter_name The name of the network adapter
 */
const char *get_mac_address(const char *adapter_name);

/*
 * Prints packet body to stdout
 */
void print_packet(dhcp_packet const *packet);

/*
 * Converts DHCP-option to array of bytes
 */
const uint8_t *option_to_byte_array(dhcp_option option);

/*
 * Gets the length of the DHCP-option
 */
uint8_t length(dhcp_option o);
#endif // DHCP_CLIENT_HELPERS_H
