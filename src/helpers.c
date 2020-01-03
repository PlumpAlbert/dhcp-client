//
// Created by plump on 1/3/20.
//
#include "../include/helpers.h"

const char *get_mac_address(const char *adapter_name) {
  struct ifreq request;
  int socket_fd;
  // Opening socket
  if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(2);
  }

  // Getting MAC-address of the computer
  strcpy(request.ifr_name, adapter_name);
  if (ioctl(socket_fd, SIOCGIFHWADDR, &request) < 0) {
    perror("ioctl");
    exit(2);
  }
  const char *mac = request.ifr_hwaddr.sa_data;
  return mac;
}