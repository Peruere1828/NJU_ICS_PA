#include "cpu/instr.h"

make_instr_func(ret_near) {
  opr_src.type = OPR_MEM;
  opr_src.sreg = SREG_SS;
  opr_src.data_size = data_size;
  opr_src.addr = cpu.esp;

  operand_read(&opr_src);
  print_asm_1("ret", "", 1, &opr_src);

  cpu.eip = opr_src.val;
  if (data_size == 16) {
    cpu.eip &= 0xffff;
  }

  cpu.esp += data_size / 8;

  return 0;
}

make_instr_func(ret_near_imm16) {
  opr_src.type = OPR_IMM;
  opr_src.sreg = SREG_CS;
  opr_src.data_size = 16;
  opr_src.addr = eip + 1;
  operand_read(&opr_src);
  opr_dest.type = OPR_MEM;
  opr_dest.sreg = SREG_SS;
  opr_dest.data_size = data_size;
  opr_dest.addr = cpu.esp;
  operand_read(&opr_dest);
  cpu.eip = opr_dest.val;
  if (data_size == 16) {
    cpu.eip &= 0xffff;
  }
  cpu.esp += data_size / 8;
  cpu.esp += opr_src.val;
  print_asm_1("ret_imm16", "", 3, &opr_dest);
  return 0;
}