#include "cpu/instr.h"

int leave(uint32_t eip, uint8_t opcode) {
  cpu.esp = cpu.ebp;
  opr_src.type = OPR_MEM;
  opr_src.addr = cpu.esp;
  opr_src.data_size = data_size;

  opr_dest.type = OPR_REG;
  opr_dest.addr = REG_EBP;
  opr_dest.data_size = data_size;
  operand_read(&opr_src);
  opr_dest.val = opr_src.val;
  cpu.esp += data_size / 8;
  operand_write(&opr_dest);
  print_asm_0("leave", "", 1);
  opr_src.data_size = 32;
  opr_src.addr = cpu.esp;
  operand_read(&opr_src);
  // printf("esp: %u %u\n",cpu.esp,opr_src.val);
  return 1;
}
