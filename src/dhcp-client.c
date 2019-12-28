#include "dhcp-client.h"

#define MAC_ADDRESS_LENGTH 6
#define MAX_RELAY_HOPS 30

#define IP_BROADCAST 0xFFFFFFFF

/**
 * Returns constant pointer to MAC address of the adapter_name
 */
unsigned char *const get_mac_address(const char *adapter_name) {
  struct ifreq request;
  int socket_fd;
  // Opening socket
  if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    _exit(2);
  }

  // Getting MAC-address of the computer
  strcpy(request.ifr_name, adapter_name);
  if (ioctl(socket_fd, SIOCGIFHWADDR, &request) < 0) {
    perror("ioctl");
    _exit(2);
  }
  unsigned char *const mac = (unsigned char *)request.ifr_hwaddr.sa_data;
  return mac;
}

/**
 * Creates DHCP messages
 */
dhcp_packet *const create_dhcp_message(unsigned char const *mac_address,
                                       const unsigned char *options,
                                       int options_len) {
  dhcp_packet *const packet = malloc(sizeof(uint8_t));
  packet->op = DHCPDISCOVER;
  packet->htype = HTYPE_ETHERNET_10MB;
  packet->hlen = MAC_ADDRESS_LENGTH;
  packet->hops = MAX_RELAY_HOPS;
  packet->xid = (uint32_t)rand();
  packet->secs = 0;
  packet->flags = 0;
  packet->ciaddr.s_addr = 0;
  packet->yiaddr.s_addr = 0;
  packet->siaddr.s_addr = 0;
  packet->giaddr.s_addr = 0;
  memcpy(packet->chaddr, mac_address, MAC_ADDRESS_LENGTH);
  memset(packet->sname, 0, DHCP_SNAME_LEN);
  memset(packet->file, 0, DHCP_FILE_LEN);
  memcpy(packet->options, options, options_len);
  return packet;
}