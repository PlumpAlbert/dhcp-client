#include "../include/dhcp-client.h"

#define MAC_ADDRESS_LENGTH 6
#define MAX_RELAY_HOPS 30

dhcp_packet *discovery(uint8_t adapter_type, const char *adapter_name) {
  // Preparation for packaging
  const char *mac = get_mac_address(adapter_name);
  // Allocate memory for packet
  dhcp_packet *const packet = malloc(sizeof(dhcp_packet));
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
  packet->options = malloc(sizeof(MAGIC_COOKIE) * sizeof(uint8_t));
  memcpy(packet->options, MAGIC_COOKIE, sizeof(MAGIC_COOKIE));
  //  memcpy(packet->options + (uint8_t)4, options, options_len);
  //  memcpy(packet->options, options, options_len);
  return packet;
}
