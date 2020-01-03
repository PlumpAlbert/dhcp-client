#include "../include/dhcp-client.h"
#include "../include/dhcp_option.h"

#define MAC_ADDRESS_LENGTH 6
#define MAX_RELAY_HOPS 30

dhcp_packet *add_option(dhcp_packet *packet, uint8_t type, uint8_t len,
                        uint8_t data[]) {
  // Copying packet
  dhcp_packet *p = malloc(sizeof(*packet));
  memcpy(p, packet, sizeof(*packet));

  // Creating DHCP-option
  dhcp_option option = {.type = type, .length = len};
  option.data = malloc(len);
  memcpy(option.data, data, len);

  // Allocating new options array
  int8_t option_length = length(option);
  unsigned long options_length = strlen((char *)packet->options);
  p->options = malloc(option_length + options_length);
  memcpy(p->options, packet->options, options_length);
  memcpy(p->options, option_to_byte_array(option), option_length);
  return p;
}

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
  //  // Adding options
  //  dhcp_option option;
  //  option.type = DHCP_OPTION_MESSAGE_TYPE;
  //  option.length = 0x01;
  //  option.data = malloc(sizeof(uint8_t));
  //  option.data[0] = DHCPDISCOVER;
  //  const uint8_t len = length(option);
  //  packet->options = malloc(sizeof(MAGIC_COOKIE) + len);
  //  memcpy(packet->options, MAGIC_COOKIE, sizeof(MAGIC_COOKIE));
  //  memcpy(packet->options + sizeof(MAGIC_COOKIE),
  //  option_to_byte_array(option),
  //         len);
  uint8_t *q = (uint8_t *){DHCPDISCOVER};
  dhcp_packet *p = add_option(packet, DHCP_OPTION_MESSAGE_TYPE, 1, q);
  free(packet->options);
  free(packet);
  return p;
}