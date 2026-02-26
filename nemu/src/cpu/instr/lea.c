#include "cpu/instr.h"

int lea(uint32_t eip, uint8_t opcode) {
  int len = 1;
  opr_src.data_size = data_size;
  opr_dest.data_size = 32;
  len += modrm_r_rm(eip + 1, &opr_dest, &opr_src);
  print_asm_2(
      "lea",
      opr_dest.data_size == 8 ? "b" : (opr_dest.data_size == 16 ? "w" : "l"),
      len, &opr_src, &opr_dest);
//   operand_read(&opr_src);
//   operand_read(&opr_dest);
  opr_dest.val = opr_src.addr;
  operand_write(&opr_dest);
  return len;
}