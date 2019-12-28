#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dhcp-client.h"

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    printf("Usage of %s:\n%s <interface_name>", argv[0], argv[0]);
    return 1;
  }
  printf("Getting MAC address of the \"%s\"...\n", argv[1]);
  unsigned char *const mac = get_mac_address(argv[1]);
  printf("MAC address is: %02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1],
         mac[2], mac[3], mac[4], mac[5]);
  return 0;
}