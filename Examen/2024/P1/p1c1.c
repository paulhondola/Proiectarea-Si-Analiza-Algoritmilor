// name_of_program 0xC1E20C02 255.255.255.0

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef union {
  uint32_t address;
  struct {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
  } bytes;
} ip_address;

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Usage: %s <ip> <mask>\n", argv[0]);
    return 1;
  }

  ip_address ip, mask, network;

  sscanf(argv[1], "%X", &ip.address);
  sscanf(argv[2], "%hhu.%hhu.%hhu.%hhu", &mask.bytes.a, &mask.bytes.b,
         &mask.bytes.c, &mask.bytes.d);

  network.address = ip.address & mask.address;

  printf("IP: %d.%d.%d.%d\n", ip.bytes.a, ip.bytes.b, ip.bytes.c, ip.bytes.d);
  printf("Mask: %d.%d.%d.%d\n", mask.bytes.a, mask.bytes.b, mask.bytes.c,
         mask.bytes.d);
  printf("Network: %d.%d.%d.%d\n", network.bytes.a, network.bytes.b,
         network.bytes.c, network.bytes.d);
  return 0;
}
