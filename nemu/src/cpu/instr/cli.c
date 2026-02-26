#include "cpu/instr.h"

int cli(uint32_t eip, uint8_t opcode){
    int len = 1;
    cpu.eflags.IF = 0;
    return len;
}
