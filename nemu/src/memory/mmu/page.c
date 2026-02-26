#include "cpu/cpu.h"
#include "memory/memory.h"

// #define DIR_MASK111 0xffc00000
// #define PAGE_MASK111 0x003ff000
// #define OFFSET_MASK111 0x00000fff

extern uint8_t hw_mem[];

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr) {
#ifndef TLB_ENABLED
  uint32_t dirid = (laddr >> 22) & 0x3ff;
  uint32_t pageid = (laddr >> 12) & 0x3ff;
  uint32_t offset = laddr & 0xfff;
  // uint32_t page_start =
  //     (uint32_t)(hw_mem) + (cpu.cr3.pdb << 12);
  PDE dir_entry =
      *((PDE *)(hw_mem + (cpu.cr3.pdb << 12) + dirid * sizeof(PDE)));
  assert(dir_entry.present == 1);
  PTE pgtbl_entry =
      *((PTE *)(hw_mem + (dir_entry.page_frame << 12) + pageid * sizeof(PTE)));
  assert(pgtbl_entry.present == 1);
  return (pgtbl_entry.page_frame << 12) + offset;
#else
  return tlb_read(laddr) | (laddr & PAGE_MASK);
#endif
}
