#include "cpu/instr.h"

int sti(uint32_t eip, uint8_t opcode){
    int len = 1;
    cpu.eflags.IF = 1;
    return len;
}
