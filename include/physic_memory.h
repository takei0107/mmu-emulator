#ifndef PHYSIC_MEMORY_H
#define PHYSIC_MEMORY_H

#include<stdint.h>
#include<stdlib.h>

#include"memory.h"

// 物理メモリ
typedef struct {
	memory_cell_t *cells;
	size_t size;
} physic_memory_t;

physic_memory_t *init_physic_memory(size_t size);

memory_cell_t physic_memory_get_cell(physic_memory_t *physic_memory, memory_addr_t addr);
#endif
