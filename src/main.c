#include <time.h>

#include "../include/dhcp-client.h"

int main(int argc, char const *argv[]) {
  srand(time(0));
  if (argc < 2) {
    printf("Usage of %s:\n%s <interface_name>", argv[0], argv[0]);
    return 1;
  }
  printf("Creating DHCP Discovery packet\n");
  uint8_t options[] = {DHCP_OPTION_MESSAGE_TYPE, 0x01, DHCPDISCOVER,
                       DHCP_OPTION_END};
  dhcp_packet *packet = discovery(HTYPE_IEEE_802, argv[1]);
  print_packet(packet);
  send_packet(packet);
  return 0;
}