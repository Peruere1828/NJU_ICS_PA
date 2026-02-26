#include "cpu/cpu.h"

extern CPU_STATE cpu;

// AF 忽略
uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
  return __ref_alu_add(src, dest, data_size);
#else
  uint32_t mask = (0xFFFFFFFF >> (32 - data_size));
  src = (src & mask);
  dest = (dest & mask);
  uint32_t sig_src = (src >> (data_size - 1)) & 1;
  uint32_t sig_dest = (dest >> (data_size - 1)) & 1;
  uint32_t result = src + dest;
  uint32_t sig_result = (result >> (data_size - 1)) & 1;
  result = (result & mask);
  cpu.eflags.CF = (result < src && result < dest);
  cpu.eflags.SF = sig_result;
  cpu.eflags.ZF = (result == 0);
  cpu.eflags.OF = (sig_src == sig_dest && sig_src != sig_result);
  cpu.eflags.PF = 1;
  for (int i = 0; i < 8; ++i) {
    cpu.eflags.PF ^= ((result >> i) & 1);
  }
  // DF 无需设置
  return result;
#endif
}

uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
  return __ref_alu_adc(src, dest, data_size);
#else
  if (cpu.eflags.CF == 0) return alu_add(src, dest, data_size);
  uint32_t mask = (0xFFFFFFFF >> (32 - data_size));
  src = (src & mask);
  dest = (dest & mask);
  uint32_t sig_src = (src >> (data_size - 1)) & 1;
  uint32_t sig_dest = (dest >> (data_size - 1)) & 1;
  uint64_t result = (uint64_t)src + dest + 1;
  cpu.eflags.CF = (result > mask);
  uint32_t sig_result = (result >> (data_size - 1)) & 1;
  result = (result & mask);
  cpu.eflags.OF = (sig_src == sig_dest && sig_src != sig_result);
  cpu.eflags.SF = sig_result;
  cpu.eflags.ZF = (result == 0);
  cpu.eflags.PF = 1;
  for (int i = 0; i < 8; ++i) {
    cpu.eflags.PF ^= ((result >> i) & 1);
  }
  // DF 无需设置
  return result;
#endif
}

uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
  return __ref_alu_sub(src, dest, data_size);
#else
  uint32_t mask = (0xFFFFFFFF >> (32 - data_size));
  src = (src & mask);
  dest = (dest & mask);
  uint32_t sig_src = (src >> (data_size - 1)) & 1;
  uint32_t sig_dest = (dest >> (data_size - 1)) & 1;
  uint64_t result = (uint64_t)dest - src;
  uint32_t sig_result = (result >> (data_size - 1)) & 1;

  uint32_t l1 = src & ((1u << (data_size - 1)) - 1);
  uint32_t l2 = dest & ((1u << (data_size - 1)) - 1);
  if (sig_src > sig_dest || (sig_src == sig_dest && l2 < l1))
    cpu.eflags.CF = 1;
  else
    cpu.eflags.CF = 0;

  if (sig_dest == 0 && sig_src == 1 && sig_result == 1)
    cpu.eflags.OF = 1;
  else if (sig_dest == 1 && sig_src == 0 && sig_result == 0)
    cpu.eflags.OF = 1;
  else
    cpu.eflags.OF = 0;

  result = (result & mask);
  cpu.eflags.SF = sig_result;
  cpu.eflags.ZF = (result == 0);
  cpu.eflags.PF = 1;
  for (int i = 0; i < 8; ++i) {
    cpu.eflags.PF ^= ((result >> i) & 1);
  }
  // DF 无需设置
  return result;
#endif
}

uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
  return __ref_alu_sbb(src, dest, data_size);
#else
  if (cpu.eflags.CF == 0) return alu_sub(src, dest, data_size);
  uint32_t mask = (0xFFFFFFFF >> (32 - data_size));
  src = (src & mask);
  dest = (dest & mask);
  uint32_t sig_src = (src >> (data_size - 1)) & 1;
  uint32_t sig_dest = (dest >> (data_size - 1)) & 1;
  uint64_t result = (uint64_t)dest - src - 1;
  uint32_t sig_result = (result >> (data_size - 1)) & 1;

  cpu.eflags.CF = (result > mask);

  if (sig_dest == 0 && sig_src == 1 && sig_result == 1)
    cpu.eflags.OF = 1;
  else if (sig_dest == 1 && sig_src == 0 && sig_result == 0)
    cpu.eflags.OF = 1;
  else
    cpu.eflags.OF = 0;

  result = (result & mask);
  cpu.eflags.SF = sig_result;
  cpu.eflags.ZF = (result == 0);
  cpu.eflags.PF = 1;
  for (int i = 0; i < 8; ++i) {
    cpu.eflags.PF ^= ((result >> i) & 1);
  }
  // DF 无需设置
  return result;
#endif
}

uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
  return __ref_alu_mul(src, dest, data_size);
#else
  uint64_t mask = (0xFFFFFFFFFFFFFFFF >> (64 - 2 * data_size));
  //   uint32_t maskl = (0xFFFFFFFF >> (32 - data_size));
  uint64_t result = ((uint64_t)src * dest) & mask;
  if ((result >> data_size) != 0) {
    cpu.eflags.CF = cpu.eflags.OF = 1;
  } else {
    cpu.eflags.CF = cpu.eflags.OF = 0;
  }
  return result;
#endif
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
  return __ref_alu_imul(src, dest, data_size);
#else
  return ((int64_t)src * dest);
#endif
}

// need to implement alu_mod before testing
uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
  return __ref_alu_div(src, dest, data_size);
#else
  uint32_t mask = (0xFFFFFFFF >> (32 - data_size));
  uint32_t result = (dest / src) & mask;
  return result;
#endif
}

// need to implement alu_imod before testing
int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
  return __ref_alu_idiv(src, dest, data_size);
#else
  uint32_t mask = (0xFFFFFFFF >> (32 - data_size));
  int32_t result = (dest / src) & mask;
  return result;
#endif
}

uint32_t alu_mod(uint64_t src, uint64_t dest) {
#ifdef NEMU_REF_ALU
  return __ref_alu_mod(src, dest);
#else
  return dest % src;
#endif
}

int32_t alu_imod(int64_t src, int64_t dest) {
#ifdef NEMU_REF_ALU
  return __ref_alu_imod(src, dest);
#else
  return dest % src;
#endif
}

uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
  return __ref_alu_and(src, dest, data_size);
#else
  uint32_t mask = (0xFFFFFFFF >> (32 - data_size));
  uint32_t result = (src & dest);
  cpu.eflags.CF = cpu.eflags.OF = 0;
  result = (result & mask);
  cpu.eflags.SF = (result >> (data_size - 1)) & 1;
  cpu.eflags.ZF = (result == 0);
  cpu.eflags.PF = 1;
  for (int i = 0; i < 8; ++i) {
    cpu.eflags.PF ^= ((result >> i) & 1);
  }
  // DF 无需设置
  return result;
#endif
}

uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
  return __ref_alu_xor(src, dest, data_size);
#else
  uint32_t mask = (0xFFFFFFFF >> (32 - data_size));
  uint32_t result = (src ^ dest);
  cpu.eflags.CF = cpu.eflags.OF = 0;
  result = (result & mask);
  cpu.eflags.SF = (result >> (data_size - 1)) & 1;
  cpu.eflags.ZF = (result == 0);
  cpu.eflags.PF = 1;
  for (int i = 0; i < 8; ++i) {
    cpu.eflags.PF ^= ((result >> i) & 1);
  }
  // DF 无需设置
  return result;
#endif
}

uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
  return __ref_alu_or(src, dest, data_size);
#else
  uint32_t mask = (0xFFFFFFFF >> (32 - data_size));
  uint32_t result = (src | dest);
  cpu.eflags.CF = cpu.eflags.OF = 0;
  result = (result & mask);
  cpu.eflags.SF = (result >> (data_size - 1)) & 1;
  cpu.eflags.ZF = (result == 0);
  cpu.eflags.PF = 1;
  for (int i = 0; i < 8; ++i) {
    cpu.eflags.PF ^= ((result >> i) & 1);
  }
  // DF 无需设置
  return result;
#endif
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
  return __ref_alu_shl(src, dest, data_size);
#else
  uint32_t mask = (0xFFFFFFFF >> (32 - data_size));
  uint64_t operand = (dest & mask);
  uint32_t sig_dest = (operand >> (data_size - 1)) & 1;
  uint32_t result = (operand & mask);
  if (src == 1) {
    cpu.eflags.OF = sig_dest;
    cpu.eflags.CF = sig_dest;
    result = (operand << 1) & mask;
  } else {
    operand <<= src;
    cpu.eflags.CF = (operand >> data_size) & 1;
    result = (operand & mask);
  }
  cpu.eflags.SF = (result >> (data_size - 1)) & 1;
  cpu.eflags.ZF = (result == 0);
  cpu.eflags.PF = 1;
  for (int i = 0; i < 8; ++i) {
    cpu.eflags.PF ^= ((result >> i) & 1);
  }
  // DF 无需设置
  return result;
#endif
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
  return __ref_alu_shr(src, dest, data_size);
#else
  uint32_t mask = (0xFFFFFFFF >> (32 - data_size));
  uint64_t operand = (dest & mask);
  if (src == 1) {
    cpu.eflags.OF = 0;
    cpu.eflags.CF = (operand & 1);
    operand >>= 1;
  } else if (src == 0) {
    cpu.eflags.CF = 0;
  } else {
    operand >>= (src - 1);
    cpu.eflags.CF = (operand & 1);
    operand >>= 1;
  }

  uint32_t result = (operand & mask);
  cpu.eflags.SF = (result >> (data_size - 1)) & 1;
  cpu.eflags.ZF = (result == 0);
  cpu.eflags.PF = 1;
  for (int i = 0; i < 8; ++i) {
    cpu.eflags.PF ^= ((result >> i) & 1);
  }
  // DF 无需设置
  return result;
#endif
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
  return __ref_alu_sar(src, dest, data_size);
#else
  uint32_t mask = (0xFFFFFFFF >> (32 - data_size));
  uint64_t operand = (dest & mask);
  uint32_t sig_dest = (operand >> (data_size - 1)) & 1;
  if (src == 1) {
    cpu.eflags.OF = 0;
    cpu.eflags.CF = (operand & 1);
    operand >>= 1;
  } else if (src == 0) {
    cpu.eflags.CF = 0;
  } else {
    operand >>= (src - 1);
    cpu.eflags.CF = (operand & 1);
    operand >>= 1;
  }
  if (sig_dest == 1) {
    operand |= ((mask >> (data_size - src)) << (data_size - src));
  }

  uint32_t result = (operand & mask);
  cpu.eflags.SF = (result >> (data_size - 1)) & 1;
  cpu.eflags.ZF = (result == 0);
  cpu.eflags.PF = 1;
  for (int i = 0; i < 8; ++i) {
    cpu.eflags.PF ^= ((result >> i) & 1);
  }
  // DF 无需设置
  return result;
#endif
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
  return __ref_alu_sal(src, dest, data_size);
#else
  return alu_shl(src, dest, data_size);
#endif
}
