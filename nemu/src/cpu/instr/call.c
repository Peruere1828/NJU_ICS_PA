#include "cpu/instr.h"

make_instr_func(call_near) {
  OPERAND rel;
  rel.type = OPR_IMM;
  rel.sreg = SREG_CS;
  rel.data_size = data_size;
  rel.addr = eip + 1;

  operand_read(&rel);

  int offset = sign_ext(rel.val, data_size);
  // thank Ting Xu from CS'17 for finding this bug
  print_asm_1("call", "", 1 + data_size / 8, &rel);

  cpu.esp -= data_size / 8;
  rel.type = OPR_MEM;
  rel.data_size = data_size;
  rel.addr = cpu.esp;
  rel.val = eip + 1 + data_size / 8;
  operand_write(&rel);
  cpu.eip += offset;
  if (data_size == 16) {
    cpu.eip &= 0xffff;
  }
  return 1 + data_size / 8;
}

make_instr_func(call_near_indirect) {
  int len = 1;
  opr_src.data_size = opr_dest.data_size = data_size;
  len += modrm_rm(eip + 1, &opr_src);

  operand_read(&opr_src);
  uint32_t nxtcmd = opr_src.val;
  print_asm_1("call_ni", "", len, &opr_src);

  cpu.esp -= data_size / 8;
  opr_src.type = OPR_MEM;
  opr_src.data_size = data_size;
  opr_src.addr = cpu.esp;
  opr_src.val = eip + len;
  operand_write(&opr_src);
  cpu.eip = nxtcmd;
  if (data_size == 16) {
    cpu.eip &= 0xffff;
  }
  return 0;
}