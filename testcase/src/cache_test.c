#include "trap.h" 
#include <stdint.h>

uint8_t dump[256]__attribute__((aligned(256)));

int main() {
    // 此处跨块写
    uint32_t *p_A_tail = (uint32_t *)(dump+0x3E);
    uint32_t *p_B_head = (uint32_t *)(dump+0x40);
    // 清空B块，同时加载B块进入cache
    *p_B_head = 0x00000000;
    
    volatile uint32_t val_B_read = *p_B_head; 
    nemu_assert(val_B_read == 0);
    
    *p_A_tail = 0xDEADBEEF;
    
    nemu_assert(*p_B_head == 0xDEAD);
    HIT_GOOD_TRAP;
    return 0;
}