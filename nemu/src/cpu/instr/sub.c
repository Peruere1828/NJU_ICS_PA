#include "cpu/instr.h"
#include "cpu/alu.h"

static void instr_execute_2op() {
  operand_read(&opr_src);
  operand_read(&opr_dest);
  if(opr_src.data_size == opr_dest.data_size) {
    opr_dest.val = alu_sub(opr_src.val, opr_dest.val, opr_dest.data_size);
  } else {
    int8_t signed_8bit = (int8_t)(uint8_t)opr_src.val;
    int32_t signed_32bit = signed_8bit;
    opr_dest.val = alu_sub(signed_32bit, opr_dest.val, opr_dest.data_size);
  }
  operand_write(&opr_dest);
}

// 28~2D
make_instr_impl_2op(sub, r, rm, b)
make_instr_impl_2op(sub, r, rm, v)
make_instr_impl_2op(sub, rm, r, b)
make_instr_impl_2op(sub, rm, r, v)
make_instr_impl_2op(sub, i, a, b)
make_instr_impl_2op(sub, i, a, v)

// 80~81
make_instr_impl_2op(sub, i, rm, b)
make_instr_impl_2op(sub, i, rm, v)

// 83
make_instr_impl_2op(sub, i, rm, bv)