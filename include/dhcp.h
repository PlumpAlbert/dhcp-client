#include <netinet/ip.h>
#include <stdint.h>

#define DHCP_CHADDR 16
#define DHCP_SNAME_LEN 64
#define DHCP_FILE_LEN 128

#define BOOTREQUEST 1
#define BOOTREPLY 2

#define BOOTP_BROADCAST 32768L

#define HTYPE_ETHERNET_10MB 1
#define HTYPE_ETHERNET_3MB 2
#define HTYPE_AMATEUR_RADIO 3
#define HTYPE_PROTEON_PRONET 4
#define HTYPE_CHAOS 5
#define HTYPE_IEEE_802 6
#define HTYPE_ARCNET 7
#define HTYPE_HYPERCHANELL 8
#define HTYPE_LANSTAR 9
#define HTYPE_AUTONET_SHORT_ADDRESS 10
#define HTYPE_LOCALTALK 11
#define HTYPE_LOCALNET 12
#define HTYPE_ULTRA_LINK 13
#define HTYPE_SMDS 14
#define HTYPE_FRAME_RELAY 15
#define HTYPE_ATM_16 16
#define HTYPE_HDLC 17
#define HTYPE_FIBRE_CHANNEL 18
#define HTYPE_ATM_19 19
#define HTYPE_SERIAL_LINE 20
#define HTYPE_ATM_21 21

#define DHCP_OPTION_PAD 0
#define DHCP_OPTION_SUBNET_MASK 1
#define DHCP_OPTION_GATEWAYS 3
#define DHCP_OPTION_DNS 6
#define DHCP_OPTION_DOMAIN_NAME 15
#define DHCP_OPTION_ADDRESS_REQUEST 50
#define DHCP_OPTION_LEASE_TIME 51
#define DHCP_OPTION_MESSAGE_TYPE 53
#define DHCP_OPTION_SERVER_ID 54
#define DHCP_OPTION_PARAMETER_LIST 55
#define DHCP_OPTION_RENEWAL_TIME 58
#define DHCP_OPTION_REBINDING_TIME 59
#define DHCP_OPTION_CLASS_ID 60
#define DHCP_OPTION_CLIENT_ID 61
#define DHCP_OPTION_END 255

#define DHCPDISCOVER 1
#define DHCPOFFER 2
#define DHCPREQUEST 3
#define DHCPDECLINE 4
#define DHCPACK 5
#define DHCPNAK 6
#define DHCPRELEASE 7
#define DHCPINFORM 8

#define MAGIC_COOKIE                                                           \
  (uint8_t[]) { 0x63, 0x82, 0x53, 0x63 }

typedef struct {
  /* 0: Message opcode/type */
  uint8_t op;
  /* 1: Hardware address type (net/if_types.h) */
  uint8_t htype;
  /* 2: Hardware address length */
  uint8_t hlen;
  /* 3: Number of relay agent hops from client */
  uint8_t hops;
  /* 4: Transaction ID */
  uint32_t xid;
  /* 8: Seconds since client started looking */
  uint16_t secs;
  /* 10: Flag bits */
  uint16_t flags;
  /* 12: Client IP address (if already in use) */
  struct in_addr ciaddr;
  /* 16: Client IP address (your IP address) */
  struct in_addr yiaddr;
  /* 20: Server IP address */
  struct in_addr siaddr;
  /* 24: DHCP-Relay agent IP address (Gateway IP address) */
  struct in_addr giaddr;
  /* 28: Client hardware address (MAC-address) */
  unsigned char chaddr[DHCP_CHADDR];
  /* 44: Optional server host name, null terminated string */
  unsigned char sname[DHCP_SNAME_LEN];
  /**
   * 108: Boot file name, null terminated string.
   * "generic" name or null in DHCPDISCOVER,
   * fully qualified directory-path name in DHCPOFFER
   */
  unsigned char file[DHCP_FILE_LEN];
  /* 136: DHCP options */
  uint8_t *options;
} dhcp_packet;
