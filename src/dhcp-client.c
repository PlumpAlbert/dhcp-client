#include "../include/dhcp-client.h"
#include <net/if.h>

#define MAC_ADDRESS_LENGTH 6
#define MAX_RELAY_HOPS 30
#define OPTION_HEADER_LEN 2

dhcp_packet *add_option(dhcp_packet *packet, uint8_t type, uint8_t len,
                        uint8_t data[]) {
  // Copying packet
  dhcp_packet *p = malloc(sizeof(dhcp_packet));
  memcpy(p, packet, sizeof(dhcp_packet));

  // Allocating new options array
  size_t old_options_len = strlen((char *)packet->options);
  size_t new_options_len = old_options_len + OPTION_HEADER_LEN + len + 1;
  p->options = malloc(new_options_len);
  memset(p->options, 0, new_options_len);
  memcpy(p->options, packet->options, old_options_len);
  p->options[old_options_len] = type;
  p->options[old_options_len + 1] = len;
  memcpy(&p->options[old_options_len + 2], data, len);
  return p;
}

dhcp_packet *discovery(uint8_t adapter_type, const char *adapter_name) {
  // Preparation for packaging
  const unsigned char *mac = get_mac_address(adapter_name);
  printf("MAC address of the \"%s\" interface is - ", adapter_name);
  for (int i = 0; i < MAC_ADDRESS_LENGTH - 1; ++i) {
    printf("%02X:", mac[i]);
  }
  printf("%02X\n", mac[MAC_ADDRESS_LENGTH - 1]);
  // Allocate memory for packet
  dhcp_packet *const packet = malloc(sizeof(dhcp_packet));
  memset(packet, 0, sizeof(dhcp_packet));
  packet->op = DHCPDISCOVER;
  packet->htype = adapter_type;
  packet->hlen = MAC_ADDRESS_LENGTH;
  packet->hops = MAX_RELAY_HOPS;
  packet->xid = (uint32_t)rand();
  packet->secs = 0;
  packet->flags = 0;
  packet->ciaddr.s_addr = 0;
  packet->yiaddr.s_addr = 0;
  packet->siaddr.s_addr = 0;
  packet->giaddr.s_addr = 0;
  memcpy(packet->chaddr, mac, MAC_ADDRESS_LENGTH);
  memset(packet->sname, 0, DHCP_SNAME_LEN);
  memset(packet->file, 0, DHCP_FILE_LEN);
  packet->options = malloc(sizeof(MAGIC_COOKIE) + 1);
  memcpy(packet->options, MAGIC_COOKIE, sizeof(MAGIC_COOKIE));
  packet->options[sizeof(MAGIC_COOKIE)] = 0;
  uint8_t q[1] = {DHCPDISCOVER};
  dhcp_packet *p = add_option(packet, DHCP_OPTION_MESSAGE_TYPE, 1, q);
  free(packet->options);
  free(packet);
  return p;
}