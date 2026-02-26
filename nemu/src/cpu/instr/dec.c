#include "cpu/instr.h"
#include "cpu/alu.h"

static void instr_execute_1op() {
  operand_read(&opr_src);
  opr_src.val = alu_sub(1, opr_src.val, opr_src.data_size);
  operand_write(&opr_src);
}

// 40~48
make_instr_impl_1op(dec, r, v)

// FE~FF
/// BUG: 这个是否存在？
make_instr_impl_1op(dec, rm, b)
make_instr_impl_1op(dec, rm, v)