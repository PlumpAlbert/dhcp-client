//
// Created by plump on 1/3/20.
//

#ifndef DHCP_CLIENT_DHCP_OPTION_H
#define DHCP_CLIENT_DHCP_OPTION_H
#include <unitypes.h>
typedef struct {
  uint8_t type;
  uint8_t length;
  uint8_t *data;
} dhcp_option;
#endif // DHCP_CLIENT_DHCP_OPTION_H
