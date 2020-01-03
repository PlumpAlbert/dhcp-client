#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "dhcp.h"
#include "helpers.h"

/**
 * Creates DHCP Discover message
 * @param adapter_name The name of the network adapter to use for DHCP message
 * creation
 * @param adapter_type The type of the network adapter
 */
dhcp_packet *discovery(uint8_t adapter_type, const char *adapter_name);
