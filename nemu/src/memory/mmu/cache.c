#include "memory/mmu/cache.h"

#include "memory/memory.h"
#include "stdlib.h"
#include "unistd.h"

#define CACHE_SETS 128  // 组数
#define CACHE_WAYS 8    // 路数/组内块数
#define BLOCK_SIZE 64   // 块大小 64B

struct Cache_Set {
  struct Cache_Line {
    bool valid;                // 有效位
    uint32_t tag;              // 地址
    uint8_t data[BLOCK_SIZE];  // 数据块
  } line[CACHE_WAYS];
} cache[CACHE_SETS];

// init the cache
void init_cache() {
  for (int i = 0; i < CACHE_SETS; i++) {
    for (int j = 0; j < CACHE_WAYS; j++) cache[i].line[j].valid = false;
  }
  // printf("MEMO START %x\n", (unsigned int)(hw_mem));
  // printf("CACHE START %x\n", (unsigned int)(cache));
}

uint32_t get_set(paddr_t paddr) { return (paddr >> 6) & 0x7f; }

uint32_t get_tag(paddr_t paddr) { return (paddr >> 13) & 0x7ffff; }

uint32_t get_addr(paddr_t paddr) { return paddr & 0x3f; }

uint32_t get_memaddr(paddr_t paddr) { return paddr & 0xffffffc0; }

// write-through + not write-allocate
void cache_write(paddr_t paddr, size_t len, uint32_t data) {
  uint32_t remain = len;
  uint32_t offset = 0;

  while (remain > 0) {
    uint32_t addr = get_addr(paddr + offset);
    uint32_t this_len =
        (addr + remain <= BLOCK_SIZE) ? remain : (BLOCK_SIZE - addr);

    // write-through: always write to memory
    memcpy(hw_mem + paddr + offset, ((uint8_t*)&data) + offset, this_len);

    // try to find a hit
    uint32_t set_number = get_set(paddr + offset);
    uint32_t tag_number = get_tag(paddr + offset);

    for (int i = 0; i < CACHE_WAYS; i++) {
      if (cache[set_number].line[i].valid &&
          cache[set_number].line[i].tag == tag_number) {
        // hit → update cache
        memcpy(&cache[set_number].line[i].data[addr],
               ((uint8_t*)&data) + offset, this_len);
        break;
      }
      // not write-allocate: do nothing on miss
    }

    offset += this_len;
    remain -= this_len;
  }
}

// read data from cache
// 我们不能！！！假装这里不可能发生跨块的访问
uint32_t cache_read(paddr_t paddr, size_t len) {
  uint32_t set_number = get_set(paddr);
  uint32_t tag_number = get_tag(paddr);
  uint32_t addr = get_addr(paddr);
  uint32_t memaddr = get_memaddr(paddr);
  uint32_t ret = 0, ret2 = 0;
  for (int i = 0; i < CACHE_WAYS; i++) {
    if (cache[set_number].line[i].valid &&
        cache[set_number].line[i].tag == tag_number) {
      // memcpy(&ret, hw_mem + paddr, len);
      if (addr + len - 1 < 64) {
        memcpy(&ret, &cache[set_number].line[i].data[addr], len);
      } else {
        memcpy(&ret, &cache[set_number].line[i].data[addr], 64 - addr);
        ret2 = cache_read(paddr - addr + 64, len - (64 - addr));
        ret |= ret2 << (8 * (64 - addr));
      }
      return ret;
    }
  }

  // uint32_t memaddr = get_memaddr(paddr);
  // 不命中
  for (int i = 0; i < CACHE_WAYS; i++) {
    if (!cache[set_number].line[i].valid) {
      cache[set_number].line[i].valid = true;
      cache[set_number].line[i].tag = tag_number;
      // for (int j = 0; j < 16; j++) printf("%x ", hw_mem[memaddr + j]);
      memcpy(cache[set_number].line[i].data, hw_mem + memaddr, BLOCK_SIZE);
      memcpy(&ret, hw_mem + paddr, len);
      return ret;
    }
  }
  // 触发替换
  uint32_t repl = rand() % CACHE_WAYS;
  cache[set_number].line[repl].tag = tag_number;
  memcpy(cache[set_number].line[repl].data, hw_mem + memaddr, BLOCK_SIZE);
  memcpy(&ret, hw_mem + paddr, len);
  return ret;
}
