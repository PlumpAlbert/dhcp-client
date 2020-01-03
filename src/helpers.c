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
  printf("|       MAGIC COOKIE       |\n");
  printf("|--------------------------|\n");
  printf("|    %d   %d   %d    %d   |\n", p->options[0], p->options[1],
         p->options[2], p->options[3]);
  printf("|==========================|\n");
  printf("|          OPTIONS         |\n");
  printf("|--------------------------|\n");
  for (size_t i = 4; i < strlen((char *)p->options);) {
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

const uint8_t *option_to_byte_array(dhcp_option option) {
  uint8_t *arr = malloc(length(option));
  arr[0] = option.type;
  arr[1] = option.length;
  memcpy(arr + 2, option.data, option.length);
  return arr;
}

uint8_t length(dhcp_option o) {
  return sizeof(o.type) + sizeof(o.length) + o.length;
}