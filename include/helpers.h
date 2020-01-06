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
const unsigned char *get_mac_address(const char *adapter_name);

/*
 * Prints packet body to stdout
 */
void print_packet(dhcp_packet const *packet);

/*
 * Converts DHCP-packet to array of bytes
 */
const uint8_t *packet_to_byte_array(dhcp_packet *packet, unsigned long *const data_len);

/*
 * Opens socket for the network adapter
 * @param adapter_name - Name of the network adapter to use for DHCP message
 * creation
 */
int open_socket(const char *adapter_name);

void send_packet(int, dhcp_packet *);
#endif // DHCP_CLIENT_HELPERS_H
