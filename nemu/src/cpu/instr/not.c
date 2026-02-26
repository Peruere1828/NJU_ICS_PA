#include "cpu/instr.h"
#include "cpu/alu.h"

static void instr_execute_1op() {
  operand_read(&opr_src);
  uint32_t mask = (0xFFFFFFFF >> (32 - data_size));
  opr_src.val ^= mask;
  operand_write(&opr_src);
}

// F6~F7
make_instr_impl_1op(not, rm, b) 
make_instr_impl_1op(not, rm, v)