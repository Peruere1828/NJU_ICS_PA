#include "cpu/instr.h"

make_instr_func(lgdt) {
  int len = 1;
  opr_src.data_size = 16;
  len += modrm_rm(eip + 1, &opr_src);
  operand_read(&opr_src);
  cpu.gdtr.limit = opr_src.val;
  opr_src.addr += 2;
  // 32位地址
  opr_src.data_size = 32;
  operand_read(&opr_src);
  cpu.gdtr.base = opr_src.val;
  return len;
}
