#include "cpu/instr.h"
#include "cpu/intr.h"

/*
Put the implementations of `int' instructions here.

Special note for `int': please use the instruction name `int_' instead of `int'.
*/

make_instr_func(int_) {
  // int len = 1;
  opr_dest.type = OPR_IMM;
  opr_dest.data_size = 8;
  opr_dest.addr = eip + 1;
  opr_dest.sreg = SREG_CS;
  operand_read(&opr_dest);
  print_asm_1("int", "", 2, &opr_dest);
  raise_sw_intr(opr_dest.val);
  return 0;
}