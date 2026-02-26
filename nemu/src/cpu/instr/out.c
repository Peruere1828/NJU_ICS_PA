#include "cpu/instr.h"
#include "device/port_io.h"

make_instr_func(out_i_b) {
  int len = 1;
  opr_src.type = OPR_IMM;
  opr_src.sreg = SREG_CS;
  opr_src.addr = eip + 1;
  opr_src.data_size = 8;
  operand_read(&opr_src);
  len += opr_src.data_size / 8;
  opr_dest.type = OPR_REG;
  opr_dest.addr = REG_AL;
  opr_dest.data_size = 8;
  operand_read(&opr_dest);
  print_asm_1("out_i", "", len, &opr_src);
  pio_write(opr_src.val, 1, opr_dest.val);
  return len;
}

make_instr_func(out_i_v) {
  int len = 1;
  opr_src.type = OPR_IMM;
  opr_src.sreg = SREG_CS;
  opr_src.addr = eip + 1;
  opr_src.data_size = 8;
  operand_read(&opr_src);
  len += opr_src.data_size / 8;
  opr_dest.type = OPR_REG;
  if (data_size == 16)
    opr_dest.addr = REG_AX;
  else
    opr_dest.addr = REG_EAX;
  opr_dest.data_size = data_size;
  operand_read(&opr_dest);
  print_asm_1("out_i", "", len, &opr_src);
  pio_write(opr_src.val, data_size / 8, opr_dest.val);
  return len;
}

make_instr_func(out_d_b) {
  int len = 1;
  opr_src.type = OPR_REG;
  opr_src.addr = REG_DX;
  opr_src.data_size = 16;
  operand_read(&opr_src);
  opr_dest.type = OPR_REG;
  opr_dest.addr = REG_AL;
  opr_dest.data_size = 8;
  operand_read(&opr_dest);
  print_asm_0("out_d", "", len);
  pio_write(opr_src.val, 1, opr_dest.val);
  return len;
}

make_instr_func(out_d_v) {
  int len = 1;
  opr_src.type = OPR_REG;
  opr_src.addr = REG_DX;
  opr_src.data_size = 16;
  operand_read(&opr_src);
  print_asm_0("out_d", "", len);
  opr_dest.type = OPR_REG;
  if (data_size == 16)
    opr_dest.addr = REG_AX;
  else
    opr_dest.addr = REG_EAX;
  opr_dest.data_size = data_size;
  operand_read(&opr_dest);
  pio_write(opr_src.val, data_size / 8, opr_dest.val);
  return len;
}