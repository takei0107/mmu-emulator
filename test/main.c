#include<stdio.h>

#include<assert.h>

#include"physic_memory.h"
#include"page.h"
#include"mmu.h"

// エミュレーター
#include"emu/cpu.h"
#include"emu/kernel.h"

// 1ページあたりのサイズ
#define PAGE_SIZE (4 * 1024)

// 物理メモリサイズ
#define PHYSIC_MEMORY_SIZE (1024 * 1024)

// ページ数
#define PAGE_NUMS 64

int main(void)
{
	physic_memory_t *physic_memory;
	page_table_t *page_table;
	mmu_t *mmu;

	// エミュレーター
	cpu_emu_t *cpu_emu;
	kernel_emu_t *kernel_emu;

	// 物理メモリ
	physic_memory = init_physic_memory(PHYSIC_MEMORY_SIZE);

	// ページテーブル
	page_table = init_page_table(PAGE_NUMS);

	// カーネル
	kernel_emu = init_kernel_emu(physic_memory, page_table);

	// mmu
	mmu = init_mmu(physic_memory, page_table, PAGE_SIZE);

	cpu_emu = init_cpu_emu(mmu, kernel_emu);

	physic_memory->cells[1] = 9;
	physic_memory->cells[4444] = 7;
	// regAの値+offsetのアドレスをdstにロード
	cpu_emu_registere_ins(cpu_emu, LOAD, 0, 0, 1, 1);
	cpu_emu_registere_ins(cpu_emu, LOAD, 0, 0, 2, 4444);

	cpu_emu_fetch_exec_cycle(cpu_emu);

	assert(cpu_emu->sharede_reg[1] == 9);
	assert(cpu_emu->sharede_reg[2] == 7);
}
