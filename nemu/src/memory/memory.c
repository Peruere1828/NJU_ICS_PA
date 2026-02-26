#include "memory/memory.h"

#include <memory.h>
#include <stdio.h>

#include "cpu/cpu.h"
#include "device/mm_io.h"
#include "nemu.h"

uint8_t hw_mem[MEM_SIZE_B];

uint32_t hw_mem_read(paddr_t paddr, size_t len) {
  uint32_t ret = 0;
  memcpy(&ret, hw_mem + paddr, len);
  return ret;
}

void hw_mem_write(paddr_t paddr, size_t len, uint32_t data) {
  memcpy(hw_mem + paddr, &data, len);
}

uint32_t paddr_read(paddr_t paddr, size_t len) {
  uint32_t ret = 0;
  int port = is_mmio(paddr);
  if (port != -1) {
    return mmio_read(paddr, len, port);
  }
#ifdef CACHE_ENABLED
  ret = cache_read(paddr, len);
#else
  ret = hw_mem_read(paddr, len);
#endif
  return ret;
}

void paddr_write(paddr_t paddr, size_t len, uint32_t data) {
  int port = is_mmio(paddr);
  if (port != -1) {
    mmio_write(paddr, len, data, port);
    return;
  }
#ifdef CACHE_ENABLED
  cache_write(paddr, len, data);
#else
  hw_mem_write(paddr, len, data);
#endif
}

uint32_t laddr_read(laddr_t laddr, size_t len) {
  if (cpu.cr0.pg == 1) {
    if ((laddr >> 12) != ((laddr + len - 1) >> 12)) {
      paddr_t paddr = page_translate(laddr);
      uint32_t lenl = (((laddr + len - 1) >> 12) << 12) - laddr,
               lenh = len - lenl;
      uint32_t lnum = paddr_read(paddr, lenl);
      uint32_t hnum =
          paddr_read(page_translate(((laddr + len - 1) >> 12) << 12), lenh);
      return (hnum << (8 * lenl)) + lnum;
    } else {
      return paddr_read(page_translate(laddr), len);
    }
  }
  return paddr_read(laddr, len);
}

void laddr_write(laddr_t laddr, size_t len, uint32_t data) {
  if (cpu.cr0.pg == 1) {
    if ((laddr >> 12) != ((laddr + len - 1) >> 12)) {
      paddr_t paddrl = page_translate(laddr);
      paddr_t paddrh = page_translate(((laddr + len - 1) >> 12) << 12);
      uint32_t lenl = (((laddr + len - 1) >> 12) << 12) - laddr,
               lenh = len - lenl;
      uint32_t datal = data & (0xffffffff >> (32 - 8 * (lenl)));
      uint32_t datah = data >> (32 - 8 * lenl);
      paddr_write(paddrl, lenl, datal);
      paddr_write(paddrh, lenh, datah);
      return;
    } else {
      paddr_write(page_translate(laddr), len, data);
      return;
    }
  }
  paddr_write(laddr, len, data);
}

uint32_t vaddr_read(vaddr_t vaddr, uint8_t sreg, size_t len) {
  assert(len == 1 || len == 2 || len == 4);
  if (cpu.cr0.pe == 1) {
    return laddr_read(segment_translate(vaddr, sreg), len);
  } else {
    return laddr_read(vaddr, len);
  }
}

void vaddr_write(vaddr_t vaddr, uint8_t sreg, size_t len, uint32_t data) {
  assert(len == 1 || len == 2 || len == 4);
  if (cpu.cr0.pe == 1) {
    laddr_write(segment_translate(vaddr, sreg), len, data);
  } else {
    laddr_write(vaddr, len, data);
  }
}

void init_mem() {
  // clear the memory on initiation
  memset(hw_mem, 0, MEM_SIZE_B);
#ifdef CACHE_ENABLED
  init_cache();  // 初始化cache
  printf("INIT_FINISH\n");
#endif
#ifdef TLB_ENABLED
  make_all_tlb();
  init_all_tlb();
#endif
}

uint32_t instr_fetch(vaddr_t vaddr, size_t len) {
  assert(len == 1 || len == 2 || len == 4);
  return vaddr_read(vaddr, SREG_CS, len);
}

uint8_t *get_mem_addr() { return hw_mem; }
