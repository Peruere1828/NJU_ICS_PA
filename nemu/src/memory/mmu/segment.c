#include "cpu/cpu.h"
#include "memory/memory.h"

extern uint8_t hw_mem[];

// return the linear address from the virtual address and segment selector
uint32_t segment_translate(uint32_t offset, uint8_t sreg) {
  SegReg sr = cpu.segReg[sreg];
  return sr.base + offset;
}

// load the invisible part of a segment register
void load_sreg(uint8_t sreg) {
  /* TODO: load the invisibile part of the segment register 'sreg' by reading
   * the GDT. The visible part of 'sreg' should be assigned by mov or ljmp
   * already.
   */
  SegDesc* sraddr = (SegDesc*)(hw_mem + cpu.gdtr.base +
                               cpu.segReg[sreg].index * sizeof(SegReg));
  assert(sraddr->granularity == 1);
  cpu.segReg[sreg].base = (sraddr->base_31_24 << 24) +
                          (sraddr->base_23_16 << 16) + sraddr->base_15_0;
  cpu.segReg[sreg].limit = (sraddr->limit_19_16 << 16) + sraddr->limit_15_0;
  assert(cpu.segReg[sreg].base == 0 && cpu.segReg[sreg].limit == 0xfffff);
  cpu.segReg[sreg].privilege_level = sraddr->privilege_level;
}
