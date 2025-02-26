// 192.168.1.2
// C0 A8 01 02
#include <stdint.h>
#include <stdio.h>
typedef union {
  uint32_t addr;
  struct {
    uint8_t d;
    uint8_t c;
    uint8_t b;
    uint8_t a;
  };
} ipaddr;

int main(void) {
  ipaddr ip = {0xC0A80102};

  printf("%0x\n", ip.addr);
  printf("%d.%d.%d.%d\n", ip.a, ip.b, ip.c, ip.d);

  return 0;
}
