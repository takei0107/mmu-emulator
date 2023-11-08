#ifndef MMU_H
#define MMU_H

#include"physic_memory.h"
#include"page.h"
#include"memory.h"

typedef struct {
	physic_memory_t *physic_memory;
	page_table_t *page_table;
	page_size_t page_size; // 1ページあたりのサイズ
	uint8_t low_bit_length;
} mmu_t;

mmu_t *init_mmu(physic_memory_t *physic_memory, page_table_t *page_table, page_size_t page_size);

/**
 *
 * 仮想メモリに対してフェッチ命令を出す。
 * 仮想メモリから取得できた場合は、outに値が格納され、0が返る。
 * ページフォルトが発生した場合は-1が返る。
 *
 **/
int mmu_virtual_memory_fetch(mmu_t *mmu, memory_addr_t virtual_addr, memory_cell_t *out);

#endif
