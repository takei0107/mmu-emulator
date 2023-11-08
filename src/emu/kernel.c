#include"emu/kernel.h"

#include <stdio.h>

kernel_emu_t *init_kernel_emu(physic_memory_t *physic_memory, page_table_t *page_table)
{
	kernel_emu_t *kernel;
	
	kernel = (kernel_emu_t *)malloc(sizeof(kernel_emu_t));
	kernel->physic_memory = physic_memory;
	kernel->page_table = page_table;
	kernel->physic_memory_ptr = 0;

	return kernel;
}

void kernel_emu_send_signal_pagefault(kernel_emu_t *kernel, page_fault_info_t page_fault_info)
{
	page_num_size_t page_num;
	page_entry_t *entry;

	page_num = CALC_PAGE_NUM(page_fault_info.fault_addr, page_fault_info.low_bit_length);

	entry = &(kernel->page_table->entries[page_num]);

	entry->frame_addr = kernel->physic_memory_ptr;
	kernel->physic_memory_ptr += page_fault_info.page_size;
	
	printf("page fault occured. fault_addr:%d, page_num:%d, assigned:%d\n", page_fault_info.fault_addr, page_num, entry->frame_addr);

	entry->exist_bit = 1;
}
