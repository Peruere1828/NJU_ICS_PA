#include "cpu/instr.h"
#include "device/port_io.h"

make_instr_func(in_i_b) {
  int len = 1;
  opr_src.type = OPR_IMM;
  opr_src.sreg = SREG_CS;
  opr_src.addr = eip + 1;
  opr_src.data_size = 8;
  operand_read(&opr_src);
  uint32_t val = pio_read(opr_src.val, 1);
  len += opr_src.data_size / 8;
  print_asm_1("in_i", "", len, &opr_src);
  opr_dest.type = OPR_REG;
  opr_dest.addr = REG_AL;
  opr_dest.data_size = 8;
  opr_dest.val = val;
  operand_write(&opr_dest);
  return len;
}

make_instr_func(in_i_v) {
  int len = 1;
  opr_src.type = OPR_IMM;
  opr_src.sreg = SREG_CS;
  opr_src.addr = eip + 1;
  opr_src.data_size = 8;
  operand_read(&opr_src);
  uint32_t val = pio_read(opr_src.val, data_size / 8);
  len += opr_src.data_size / 8;
  print_asm_1("in_i", "", len, &opr_src);
  opr_dest.type = OPR_REG;
  if(data_size == 16) opr_dest.addr = REG_AX;
  else opr_dest.addr = REG_EAX;
  opr_dest.data_size = data_size;
  opr_dest.val = val;
  operand_write(&opr_dest);
  return len;
}

make_instr_func(in_d_b) {
  int len = 1;
  opr_src.type = OPR_REG;
  opr_src.addr = REG_DX;
  opr_src.data_size = 16;
  operand_read(&opr_src);
  uint32_t val = pio_read(opr_src.val, 1);
  print_asm_0("in_d", "", len);
  opr_dest.type = OPR_REG;
  opr_dest.addr = REG_AL;
  opr_dest.data_size = 8;
  opr_dest.val = val;
  operand_write(&opr_dest);
  return len;
}

make_instr_func(in_d_v) {
  int len = 1;
  opr_src.type = OPR_REG;
  opr_src.addr = REG_DX;
  opr_src.data_size = 16;
  operand_read(&opr_src);
  uint32_t val = pio_read(opr_src.val, data_size / 8);
  print_asm_0("in_d", "", len);
  opr_dest.type = OPR_REG;
  if(data_size == 16) opr_dest.addr = REG_AX;
  else opr_dest.addr = REG_EAX;
  opr_dest.data_size = data_size;
  opr_dest.val = val;
  operand_write(&opr_dest);
  return len;
}