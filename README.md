2025秋ICS PA i386版个人解答，仅完成必做部分。请勿抄袭。

```
### Commit 2658f36
Date: Fri Dec 5 00:00:05 2025 +0800
Message: fix bug from 3-1

nemu/src/memory/mmu/cache.c

### Commit 2fcaf1f
Date: Wed Oct 1 18:09:08 2025 +0800
Message: pa4-2: timer

kernel/src/elf/elf.c
kernel/src/irq/irq_handle.c

### Commit 0941c93
Date: Wed Oct 1 14:09:25 2025 +0800
Message: pa4-3: typing game

nemu/src/cpu/decode/opcode.c

### Commit 92fcb34
Date: Sun Sep 28 22:37:57 2025 +0800
Message: pa4-2: debug

include/config.h
kernel/src/elf/elf.c

### Commit b8891b1
Date: Sun Sep 28 21:01:32 2025 +0800
Message: pa4-2: VGA finish

include/config.h
kernel/src/elf/elf.c
kernel/src/memory/vmem.c
nemu/src/memory/memory.c

### Commit b84f817
Date: Sun Sep 28 16:58:14 2025 +0800
Message: pa4-2: keyboard

include/config.h

### Commit 4937972
Date: Sun Sep 28 15:55:52 2025 +0800
Message: pa4-2: hard disk finish

include/config.h
kernel/src/elf/elf.c

### Commit 495d6d3
Date: Sun Sep 28 15:07:23 2025 +0800
Message: pa4-2: serial finish

include/config.h
kernel/src/lib/serial.c
nemu/include/cpu/instr/in.h
nemu/include/cpu/instr/out.h
nemu/src/cpu/decode/opcode.c
nemu/src/cpu/instr/in.c
nemu/src/cpu/instr/out.c

### Commit 145b863
Date: Sat Sep 27 10:52:56 2025 +0800
Message: pa4-1.1 finish

include/config.h
nemu/include/cpu/instr/int_.h
nemu/include/cpu/instr/iret.h
nemu/include/cpu/instr/lidt.h
nemu/include/cpu/reg.h
nemu/src/cpu/decode/opcode.c
nemu/src/cpu/instr/int_.c
nemu/src/cpu/instr/iret.c
nemu/src/cpu/instr/lidt.c
nemu/src/cpu/intr.c

### Commit a2fe2f8
Date: Tue Sep 23 23:26:07 2025 +0800
Message: pa3-3: 不影响结果的修改

kernel/src/elf/elf.c
nemu/src/memory/memory.c

### Commit c16e349
Date: Tue Sep 23 23:11:30 2025 +0800
Message: pa3-3: finish

include/config.h
kernel/Makefile
kernel/src/elf/elf.c
nemu/include/cpu/reg.h
nemu/src/cpu/instr/jmp.c
nemu/src/cpu/instr/mov.c
nemu/src/cpu/instr/push.c
nemu/src/cpu/instr/ret.c
nemu/src/memory/memory.c
nemu/src/memory/mmu/page.c
nemu/src/memory/mmu/segment.c
testcase/Makefile

### Commit 5cd1389
Date: Mon Sep 15 17:25:14 2025 +0800
Message: pa3-2: finish

include/config.h
nemu/include/cpu/instr/jmp.h
nemu/include/cpu/instr/lgdt.h
nemu/include/cpu/instr/mov.h
nemu/include/cpu/reg.h
nemu/src/cpu/decode/opcode.c
nemu/src/cpu/instr/jmp.c
nemu/src/cpu/instr/lgdt.c
nemu/src/cpu/instr/mov.c
nemu/src/memory/memory.c
nemu/src/memory/mmu/segment.c

### Commit c32fd4a
Date: Thu Sep 11 23:52:01 2025 +0800
Message: pa3-1: finish

include/config.h
nemu/src/memory/memory.c
nemu/src/memory/mmu/cache.c

### Commit cf4fa32
Date: Wed Sep 10 14:50:55 2025 +0800
Message: pa2-2: finish

kernel/src/elf/elf.c
testcase/Makefile

### Commit 617fb7e
Date: Tue Sep 9 22:33:38 2025 +0800
Message: pa2-1: finish

nemu/include/cpu/instr/jmp.h
nemu/src/cpu/decode/opcode.c
nemu/src/cpu/instr/call.c
nemu/src/cpu/instr/jmp.c

### Commit b8ae86a
Date: Tue Sep 9 22:00:04 2025 +0800
Message: pa2-1: call/ret

nemu/include/cpu/instr/call.h
nemu/include/cpu/instr/cli.h
nemu/include/cpu/instr/leave.h
nemu/include/cpu/instr/neg.h
nemu/include/cpu/instr/not.h
nemu/include/cpu/instr/push.h
nemu/include/cpu/instr/ret.h
nemu/include/cpu/instr/sti.h
nemu/src/cpu/cpu.c
nemu/src/cpu/decode/opcode.c
nemu/src/cpu/instr/call.c
nemu/src/cpu/instr/cli.c
nemu/src/cpu/instr/leave.c
nemu/src/cpu/instr/neg.c
nemu/src/cpu/instr/not.c
nemu/src/cpu/instr/pop.c
nemu/src/cpu/instr/push.c
nemu/src/cpu/instr/ret.c
nemu/src/cpu/instr/sti.c

### Commit fb2c8b2
Date: Thu Sep 4 11:11:18 2025 +0800
Message: pa2-1: test, popa, pusha

nemu/include/cpu/instr/pop.h
nemu/include/cpu/instr/push.h
nemu/include/cpu/instr/test.h
nemu/src/cpu/decode/opcode.c
nemu/src/cpu/instr/pop.c
nemu/src/cpu/instr/push.c
nemu/src/cpu/instr/test.c

### Commit 02c3f92
Date: Wed Sep 3 22:30:09 2025 +0800
Message: pa2-1: addtest pass

nemu/include/cpu/instr/dec.h
nemu/include/cpu/instr/inc.h
nemu/include/cpu/instr/lea.h
nemu/include/cpu/instr_helper.h
nemu/src/cpu/decode/opcode.c
nemu/src/cpu/instr/dec.c
nemu/src/cpu/instr/inc.c
nemu/src/cpu/instr/lea.c

### Commit eae7a01
Date: Wed Sep 3 15:53:43 2025 +0800
Message: pa2-1: 8 ops和jcmp

nemu/include/cpu/instr/adc.h
nemu/include/cpu/instr/add.h
nemu/include/cpu/instr/and.h
nemu/include/cpu/instr/cmp.h
nemu/include/cpu/instr/jmp.h
nemu/include/cpu/instr/or.h
nemu/include/cpu/instr/pop.h
nemu/include/cpu/instr/push.h
nemu/include/cpu/instr/sbb.h
nemu/include/cpu/instr/sub.h
nemu/include/cpu/instr/xor.h
nemu/include/cpu/instr_helper.h
nemu/src/cpu/decode/opcode.c
nemu/src/cpu/instr/adc.c
nemu/src/cpu/instr/add.c
nemu/src/cpu/instr/and.c
nemu/src/cpu/instr/cmp.c
nemu/src/cpu/instr/jmp.c
nemu/src/cpu/instr/or.c
nemu/src/cpu/instr/pop.c
nemu/src/cpu/instr/push.c
nemu/src/cpu/instr/sbb.c
nemu/src/cpu/instr/sub.c
nemu/src/cpu/instr/xor.c

### Commit c40280e
Date: Tue Sep 2 15:04:28 2025 +0800
Message: pa1-3: 浮点乘除

nemu/src/cpu/fpu.c
nemu/src/cpu/test/fpu_test.c

### Commit 2538620
Date: Tue Sep 2 14:19:13 2025 +0800
Message: pa1-3: 浮点加减

nemu/src/cpu/fpu.c
nemu/src/cpu/test/fpu_test.c

### Commit baa72b4
Date: Mon Sep 1 19:38:05 2025 +0800
Message: pa1-2: 乘除

nemu/src/cpu/alu.c
nemu/src/cpu/test/alu_test.c

### Commit fe2079c
Date: Mon Sep 1 17:46:49 2025 +0800
Message: pa1-2: shift

nemu/src/cpu/alu.c

### Commit f7c195c
Date: Mon Sep 1 16:48:44 2025 +0800
Message: pa1-2: alu_and/xor/or

nemu/src/cpu/alu.c

### Commit da77a61
Date: Mon Sep 1 16:40:51 2025 +0800
Message: pa1-2: alu_sbb

nemu/src/cpu/alu.c
nemu/src/cpu/test/alu_test.c

### Commit cf2a61c
Date: Mon Sep 1 16:30:21 2025 +0800
Message: pa1-2: alu_adc, alu_sub

nemu/src/cpu/alu.c

### Commit 174d860
Date: Mon Sep 1 15:32:21 2025 +0800
Message: initial and pa1-2: alu_add

too long, ignore
```