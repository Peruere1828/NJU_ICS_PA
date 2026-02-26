#include "cpu/instr.h"
#include "segment.h"

make_instr_func(jmp_near) {
  OPERAND rel;
  rel.type = OPR_IMM;
  rel.sreg = SREG_CS;
  rel.data_size = data_size;
  rel.addr = eip + 1;

  operand_read(&rel);

  int offset = sign_ext(rel.val, data_size);
  // thank Ting Xu from CS'17 for finding this bug
  print_asm_1("jmp", "", 1 + data_size / 8, &rel);

  cpu.eip += offset;

  return 1 + data_size / 8;
}

make_instr_func(jmp_short) {
  OPERAND rel;
  rel.type = OPR_IMM;
  rel.sreg = SREG_CS;
  rel.data_size = 8;
  rel.addr = eip + 1;

  operand_read(&rel);

  int offset = sign_ext(rel.val, 8);
  // thank Ting Xu from CS'17 for finding this bug
  print_asm_1("jmp", "", 2, &rel);

  cpu.eip += offset;

  return 2;
}

make_instr_func(jmp_near_indirect) {
  int len = 1;
  opr_src.sreg = SREG_CS;
  opr_src.data_size = opr_dest.data_size = data_size;
  len += modrm_rm(eip + 1, &opr_src);

  operand_read(&opr_src);
  uint32_t nxtcmd = opr_src.val;
  print_asm_1("jmp_ni", "", len, &opr_src);

  cpu.eip = nxtcmd;
  if (data_size == 16) {
    cpu.eip &= 0xffff;
  }
  return 0;
}

// aka jmp_far_imm
make_instr_func(ljmp) {
  opr_src.data_size = data_size;
  opr_src.type = OPR_IMM;
  opr_src.sreg = SREG_CS;
  opr_src.addr = eip + 1;
  operand_read(&opr_src);
  cpu.eip = opr_src.val;
  if (data_size == 16) {
    cpu.eip &= 0xffff;
  }
  opr_src.data_size = 16;
  opr_src.type = OPR_IMM;
  opr_src.sreg = SREG_CS;
  opr_src.addr = eip + 1 + data_size / 8;
  operand_read(&opr_src);
  cpu.cs.val = opr_src.val;
  load_sreg(1);
  return 0;
}