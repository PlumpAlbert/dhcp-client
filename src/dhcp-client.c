#include "dhcp-client.h"

/**
 * Returns constant pointer to MAC address of the ${adapter_name}
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
