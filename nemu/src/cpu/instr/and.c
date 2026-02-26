#include "cpu/instr.h"
#include "cpu/alu.h"

static void instr_execute_2op() {
  operand_read(&opr_src);
  operand_read(&opr_dest);
  if(opr_src.data_size == opr_dest.data_size) {
    opr_dest.val = alu_and(opr_src.val, opr_dest.val, opr_dest.data_size);
  } else {
    int8_t signed_8bit = (int8_t)(uint8_t)opr_src.val;
    int32_t signed_32bit = signed_8bit;
    opr_dest.val = alu_and(signed_32bit, opr_dest.val, opr_dest.data_size);
  }
  operand_write(&opr_dest);
}

// 20~25
make_instr_impl_2op(and, r, rm, b)
make_instr_impl_2op(and, r, rm, v)
make_instr_impl_2op(and, rm, r, b)
make_instr_impl_2op(and, rm, r, v)
make_instr_impl_2op(and, i, a, b)
make_instr_impl_2op(and, i, a, v)

// 80~81
make_instr_impl_2op(and, i, rm, b)
make_instr_impl_2op(and, i, rm, v)

// 83
make_instr_impl_2op(and, i, rm, bv)