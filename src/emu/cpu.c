#include"emu/cpu.h"

#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

cpu_emu_t *init_cpu_emu(mmu_t *mmu, kernel_emu_t *kernel)
{
	cpu_emu_t *cpu_emu;
	cpu_emu = (cpu_emu_t *)malloc(sizeof(cpu_emu_t));

	cpu_emu->ops = (operation_t *)malloc(sizeof(operation_t) * OP_NUMS_MAX);
	memset(cpu_emu->ops, 0, sizeof(operation_t) * OP_NUMS_MAX);

	cpu_emu->op_nums = 0;
	cpu_emu->mmu = mmu;
	cpu_emu->kernel = kernel;

	return cpu_emu;
}

void cpu_emu_registere_ins(cpu_emu_t *cpu, OPCODE opcode, uint8_t regA, uint8_t regB, uint8_t dst, uint32_t offset)
{
	operation_t *op;

	op = cpu->ops + cpu->op_nums++;
	op->opcode = opcode;
	op->regA = regA;
	op->regB = regB;
	op->dst = dst;
	op->offset = offset;
}

int cpu_emu_fetch_exec_cycle(cpu_emu_t *cpu)
{
	int i, result;
	operation_t op;
	bool interrupted;
	memory_cell_t out;
	memory_addr_t fault_addr;
	page_fault_info_t page_fault_info;

	i = 0;
	out = 0;
	interrupted = false;

	while(i < cpu->op_nums)
	{
		if (interrupted)
		{
			page_fault_info.fault_addr = fault_addr;
			page_fault_info.low_bit_length = cpu->mmu->low_bit_length;
			page_fault_info.page_size = cpu->mmu->page_size;

			// 割り込み処理をカーネルに委譲
			kernel_emu_send_signal_pagefault(cpu->kernel, page_fault_info);
			interrupted = false;
		}
		else
		{
			op = cpu->ops[i];
			switch (op.opcode)
			{
				case LOAD:
					
					if ((result = mmu_virtual_memory_fetch(cpu->mmu, op.regA + op.offset, &out)) == -1)
					{
						// ページフォルト発生
						fault_addr = op.regA + op.offset;
						interrupted = true;
					}
					else
					{
						cpu->sharede_reg[op.dst] = out;
					}
					break;
			}
			if (!interrupted)
			{
				i++;
			}
		}
	}
}
