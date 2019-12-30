#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dhcp-client.h"

void print_packet(dhcp_packet const *p) {
  // 26 chars per line
  printf("============================\n");
  printf("| OP | HTYPE | HLEN | HOPS |\n");
  printf("|--------------------------|\n");
  printf("| %02X |   %02X  |  %02X  |  %02X  |\n", p->op, p->htype, p->hlen,
         p->hops);
  printf("|==========================|\n");
  printf("|            XID           |\n");
  printf("|--------------------------|\n");
  printf("|         0x%08X       |\n", p->xid);
  printf("|==========================|\n");
  printf("|    SECS    |    FLAGS    |\n");
  printf("|--------------------------|\n");
  printf("|   0x%04X   |    0x%04X   |\n", p->secs, p->flags);
  printf("|==========================|\n");
  printf("|          CIADDR          |\n");
  printf("|--------------------------|\n");
  printf("|      %-15s     |\n", inet_ntoa(p->ciaddr));
  printf("|==========================|\n");
  printf("|          YIADDR          |\n");
  printf("|--------------------------|\n");
  printf("|      %-15s     |\n", inet_ntoa(p->yiaddr));
  printf("|==========================|\n");
  printf("|          SIADDR          |\n");
  printf("|--------------------------|\n");
  printf("|      %-15s     |\n", inet_ntoa(p->siaddr));
  printf("|==========================|\n");
  printf("|          GIADDR          |\n");
  printf("|--------------------------|\n");
  printf("|      %-15s     |\n", inet_ntoa(p->giaddr));
  printf("|==========================|\n");
  printf("|          CHADDR          |\n");
  printf("|--------------------------|\n");
  printf("|     %02X:%02X:%02X:%02X:%02X:%02X    |\n", p->chaddr[0],
         p->chaddr[1], p->chaddr[2], p->chaddr[3], p->chaddr[4], p->chaddr[5]);
  printf("|==========================|\n");
  printf("|           SNAME          |\n");
  printf("|--------------------------|\n");
  printf("|                          |\n");
  printf("|==========================|\n");
  printf("|           FILE           |\n");
  printf("|--------------------------|\n");
  printf("|                          |\n");
  printf("|==========================|\n");
  printf("|          OPTIONS         |\n");
  printf("|--------------------------|\n");
  for (size_t i = 0; i < strlen((char *)p->options);) {
    if (i != 0) {
      printf("|==========================|\n");
    }
    if (p->options[i] == 255) {
      printf("| %02X |\n", 1);
      break;
    }
    printf("| %02d | %02d | ", p->options[i], p->options[i + 1]);
    for (size_t j = 2; j - 2 < p->options[i + 1]; ++j)
      printf("%02X", p->options[i + j]);
    printf(" |\n");
    i += 2 + p->options[i + 1];
  }
  printf("============================\n");
}

int main(int argc, char const *argv[]) {
  srand(time(0));
  if (argc < 2) {
    printf("Usage of %s:\n%s <interface_name>", argv[0], argv[0]);
    return 1;
  }
  printf("Getting MAC address of the \"%s\"...\n", argv[1]);
  unsigned char *const mac = get_mac_address(argv[1]);
  printf("MAC address is: %02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1],
         mac[2], mac[3], mac[4], mac[5]);
  printf("Creating DHCP Discovery packet\n");
  uint8_t options[] = {DHCP_OPTION_MESSAGE_TYPE, sizeof(DHCPDISCOVER),
                       DHCPDISCOVER, DHCP_OPTION_END};
  dhcp_packet *packet = dhcp_discover(mac, options, sizeof(options));
  print_packet(packet);
  return 0;
}