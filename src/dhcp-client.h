#include <net/if.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include "dhcp.h"

unsigned char *const get_mac_address(const char *adapter_name);