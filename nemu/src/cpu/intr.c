#include "cpu/intr.h"

#include "cpu/instr.h"
#include "memory/memory.h"

void raise_intr(uint8_t intr_no) {
#ifdef IA32_INTR
  // eflags
  cpu.esp -= 4;
  opr_src.type = OPR_MEM;
  opr_src.sreg = SREG_SS;
  opr_src.addr = cpu.esp;
  opr_src.data_size = 32;
  opr_src.val = cpu.eflags.val;
  operand_write(&opr_src);

  // CS
  cpu.esp -= 4;
  opr_src.addr = cpu.esp;
  opr_src.data_size = 16;
  opr_src.val = cpu.cs.val;
  operand_write(&opr_src);

  // eip
  cpu.esp -= 4;
  opr_src.addr = cpu.esp;
  opr_src.data_size = 32;
  opr_src.val = cpu.eip;
  operand_write(&opr_src);

  GateDesc* idt =
      (void*)((uint32_t)hw_mem +
              page_translate(cpu.idtr.base + intr_no * sizeof(GateDesc)));
  // 中断，清除IF
  if (idt->type == 0xe) {
    cpu.eflags.IF = 0;
  }
  // 平坦模式可以忽略idt->selector
  cpu.eip = (idt->offset_31_16 << 16) + idt->offset_15_0;
#endif
}

void raise_sw_intr(uint8_t intr_no) {
  // return address is the next instruction
  cpu.eip += 2;
  raise_intr(intr_no);
}
