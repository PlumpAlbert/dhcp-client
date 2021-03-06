#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "helpers.h"

/*
 * Adds option to the DHCP-packet
 * @param type The type of the DHCP-option
 * @param len The length of the data
 * @param data The payload of the option
 */
dhcp_packet *add_option(dhcp_packet *packet, uint8_t type, uint8_t len,
                        uint8_t *data);

/**
 * Creates DHCP Discover message
 * @param adapter_name The name of the network adapter to use for DHCP message
 * creation
 * @param adapter_type The type of the network adapter
 */
dhcp_packet *discovery(uint8_t adapter_type, const char *adapter_name);
