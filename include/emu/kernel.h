#ifndef KERNEL_EMU_H
#define KERNEL_EMU_H

#include"physic_memory.h"
#include"page.h"

typedef struct {
	physic_memory_t *physic_memory;
	page_table_t *page_table;
	memory_addr_t physic_memory_ptr;
} kernel_emu_t;

kernel_emu_t *init_kernel_emu(physic_memory_t *physic_memory, page_table_t *page_table);

void kernel_emu_send_signal_pagefault(kernel_emu_t *kernel, page_fault_info_t page_fault_info);

#endif
