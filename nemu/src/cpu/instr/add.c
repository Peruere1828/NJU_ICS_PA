#include "cpu/instr.h"
#include "cpu/alu.h"

static void instr_execute_2op() {
  operand_read(&opr_src);
  operand_read(&opr_dest);
  if(opr_src.data_size == opr_dest.data_size) {
    opr_dest.val = alu_add(opr_src.val, opr_dest.val, opr_dest.data_size);
  } else {
    int8_t signed_8bit = (int8_t)(uint8_t)opr_src.val;
    int32_t signed_32bit = signed_8bit;
    opr_dest.val = alu_add(signed_32bit, opr_dest.val, opr_dest.data_size);
  }
  operand_write(&opr_dest);
}

// 00~05
make_instr_impl_2op(add, r, rm, b)
make_instr_impl_2op(add, r, rm, v)
make_instr_impl_2op(add, rm, r, b)
make_instr_impl_2op(add, rm, r, v)
make_instr_impl_2op(add, i, a, b)
make_instr_impl_2op(add, i, a, v)

// 80~81
make_instr_impl_2op(add, i, rm, b)
make_instr_impl_2op(add, i, rm, v)

// 83
make_instr_impl_2op(add, i, rm, bv)