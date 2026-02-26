#include "cpu/instr.h"

static void instr_execute_1op() {
  operand_read(&opr_src);
  cpu.esp -= opr_src.data_size / 8;
  opr_src.type = OPR_MEM;
  opr_src.sreg = SREG_SS;
  opr_src.addr = cpu.esp;
  operand_write(&opr_src);
}

make_instr_impl_1op(push, r, v) 
make_instr_impl_1op(push, rm, v)
make_instr_impl_1op(push, i, v)

int push_i_b(uint32_t eip, uint8_t opcode) {
  int len = 1;
  opr_src.data_size = opr_dest.data_size = 8;
  opr_src.type = OPR_IMM;
  opr_src.sreg = SREG_CS;
  opr_src.addr = eip + 1;
  len += opr_src.data_size / 8;
  print_asm_1(
      "push",
      opr_src.data_size == 8 ? "b" : (opr_src.data_size == 16 ? "w" : "l"), len,
      &opr_src);
  operand_read(&opr_src);
  // push_i_b也是4字节
  cpu.esp -= 4;
  opr_src.type = OPR_MEM;
  opr_src.addr = cpu.esp;
  opr_src.val = sign_ext(opr_src.val, 32);
  opr_src.sreg = SREG_SS;
  opr_src.data_size = 32;
  operand_write(&opr_src);
  return len;
}

int pusha(uint32_t eip, uint8_t opcode) {
  int len = 1;
  print_asm_0("pusha", data_size == 8 ? "b" : (data_size == 16 ? "w" : "l"),
              len);
  uint32_t tmp = cpu.esp;
  for (int i = 0; i < 8; i++) {
    cpu.esp -= data_size / 8;
    opr_src.type = OPR_MEM;
    opr_src.sreg = SREG_SS;
    opr_src.addr = cpu.esp;
    opr_src.data_size = data_size;
    if (i == 4)
      opr_src.val = tmp;
    else
      opr_src.val = cpu.gpr[i].val;
    operand_write(&opr_src);
  }
  return len;
}