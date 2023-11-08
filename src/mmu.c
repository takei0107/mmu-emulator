#include<math.h>

#include"mmu.h"

mmu_t *init_mmu(physic_memory_t *physic_memory, page_table_t *page_table, page_size_t page_size)
{
	mmu_t *mmu;

	mmu = (mmu_t *)malloc(sizeof(mmu_t));
	mmu->physic_memory = physic_memory;
	mmu->page_table = page_table;
	mmu->page_size = page_size;

	mmu->low_bit_length = (uint8_t)log2(page_size);

	return mmu;
}

int mmu_virtual_memory_fetch(mmu_t *mmu, memory_addr_t virtual_addr, memory_cell_t *out)
{
	page_num_size_t page_num;
	page_entry_t entry;
	memory_addr_t physic_addr;

	page_num = CALC_PAGE_NUM(virtual_addr, mmu->low_bit_length);

	printf("virtual_addr:%d,low_bit_length:%d, page_num:%d\n",virtual_addr, mmu->low_bit_length, page_num);

	entry = mmu->page_table->entries[page_num];

	if (!entry.exist_bit) {
		// page fault!
		return -1;
	}

	
	// 物理アドレス
	physic_addr = entry.frame_addr | virtual_addr;
	*out = physic_memory_get_cell(mmu->physic_memory, physic_addr);

	return 0;
}

void mmu_virtual_memory_allocate(mmu_t *mmu)
{
	
}
