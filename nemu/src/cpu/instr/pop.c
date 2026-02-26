#include "cpu/instr.h"

int pop_r_v(uint32_t eip, uint8_t opcode) {
  int len = 1;
  opr_src.data_size = data_size;
  opr_src.type = OPR_MEM;
  opr_src.addr = cpu.esp;
  print_asm_1(
      "pop",
      opr_src.data_size == 8 ? "b" : (opr_src.data_size == 16 ? "w" : "l"), len,
      &opr_src);
  operand_read(&opr_src);
  cpu.esp += data_size / 8;
  opr_src.type = OPR_REG;
  opr_src.addr = opcode & 0x7;
  operand_write(&opr_src);
  return len;
}

int popa(uint32_t eip, uint8_t opcode) {
  int len = 1;
  print_asm_0("popa", data_size == 8 ? "b" : (data_size == 16 ? "w" : "l"),
              len);
  for (int i = 7; i >= 0; i--) {
    opr_src.type = OPR_MEM;
    opr_src.addr = cpu.esp;
    opr_src.data_size = data_size;
    operand_read(&opr_src);
    cpu.esp += data_size / 8;
    opr_dest.type = OPR_REG;
    opr_dest.addr = i;
    opr_dest.data_size = data_size;
    if (i != 4) {
      opr_dest.val = opr_src.val;
      operand_write(&opr_dest);
    }
  }
  return len;
}