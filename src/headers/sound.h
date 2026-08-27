#include <stdint.h>
#define __outbyte(port, val) __asm__ volatile("outb %0, %1" : : "a"((uint8_t)(val)), "Nd"((uint16_t)(port)))
#define __inbyte(port) ({ uint8_t _v; __asm__ volatile("inb %1, %0" : "=a"(_v) : "Nd"((uint16_t)(port))); _v; })


void beep_on(uint32_t frequency) {
     uint32_t div = 1193182 / frequency;
     __outbyte(0x43, 0xB6);
     __outbyte(0x42, (uint8_t)(div));
     __outbyte(0x42, (uint8_t)(div >> 8));
     uint8_t speaker_state = __inbyte(0x61);
     __outbyte(0x61, speaker_state | 3);
}
void beep_off() {
     uint8_t speaker_state = __inbyte(0x61);
     __outbyte(0x61, speaker_state & 0xFC);
}

