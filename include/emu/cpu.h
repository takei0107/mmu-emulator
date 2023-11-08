#ifndef EMU_CPU_H
#define EMU_CPU_H

#include"mmu.h"
#include"emu/kernel.h"

#define OP_NUMS_MAX 256

typedef uint32_t register_emu_t;

typedef enum {
	ADD,
	LOAD,
	STORE
} OPCODE;

typedef struct {
	OPCODE opcode;
	uint8_t regA;
	uint8_t regB;
	uint8_t dst;
	uint32_t offset;
} operation_t;

// CPUエミュレーター
typedef struct {
	register_emu_t sharede_reg[16];
	operation_t *ops;
	uint8_t op_nums;
	mmu_t *mmu;
	kernel_emu_t *kernel;
} cpu_emu_t;

cpu_emu_t *init_cpu_emu(mmu_t *mmu, kernel_emu_t *kernel);

void cpu_emu_registere_ins(cpu_emu_t *cpu, OPCODE opcode, uint8_t regA, uint8_t regB, uint8_t dst, uint32_t offset);

int cpu_emu_fetch_exec_cycle(cpu_emu_t *cpu);

#endif
