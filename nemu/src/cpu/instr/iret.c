#include "cpu/instr.h"

make_instr_func(iret) {
  // EFLAGS
  opr_src.type = OPR_MEM;
  opr_src.sreg = SREG_SS;
  opr_src.data_size = 32;
  opr_src.addr = cpu.esp + 8;
  operand_read(&opr_src);
  cpu.eflags.val = opr_src.val;

  // eip
  opr_src.addr = cpu.esp;
  operand_read(&opr_src);
  cpu.eip = opr_src.val;
  cpu.esp += 4;

  // CS
  opr_src.addr = cpu.esp;
  opr_src.data_size = 16;
  operand_read(&opr_src);
  //   uint32_t cpl = cpu.cs.rpl;  // cpl 用于后面 if
  cpu.cs.val = opr_src.val;
  cpu.esp += 4 + 4;  // CS + Throwaway Eflags

  // 手册上是有后半部分的，但是似乎nemu不实现？
  // ES
  //   opr_src.addr = cpu.esp;
  //   operand_read(&opr_src);
  //   cpu.es.val = opr_src.val;
  //   cpu.esp += 4;

  //   // DS
  //   opr_src.addr = cpu.esp;
  //   operand_read(&opr_src);
  //   cpu.ds.val = opr_src.val;
  //   cpu.esp += 4;

  //   // FS
  //   opr_src.addr = cpu.esp;
  //   operand_read(&opr_src);
  //   cpu.fs.val = opr_src.val;
  //   cpu.esp += 4;

  //   // GS
  //   opr_src.addr = cpu.esp;
  //   operand_read(&opr_src);
  //   cpu.gs.val = opr_src.val;
  //   cpu.esp += 4;

  //   if (cpu.cs.rpl > cpl) {
  //     opr_src.addr = cpu.esp;
  //     opr_src.data_size = 32;
  //     operand_read(&opr_src);
  //     uint32_t tmpesp = opr_src.val;
  //     cpu.esp += 4;
  //     opr_src.addr = cpu.esp;
  //     opr_src.data_size = 16;
  //     operand_read(&opr_src);
  //     uint32_t tmpss = opr_src.val;
  //     cpu.esp += 4;
  //     cpu.ss.val = tmpss;
  //     cpu.esp = tmpesp;
  //   }
  return 0;
}