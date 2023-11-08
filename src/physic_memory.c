#include<stdlib.h>
#include<string.h>

#include"physic_memory.h"

physic_memory_t *init_physic_memory(size_t size)
{
	physic_memory_t *memory;
	memory = (physic_memory_t *)malloc(sizeof(physic_memory_t));
	memory->cells = (memory_cell_t *)malloc(sizeof(memory_cell_t) * size);
	memory->size = size;
	memset(memory->cells, 0, (sizeof(memory_cell_t) * size));
	return memory;
}

memory_cell_t physic_memory_get_cell(physic_memory_t *physic_memory, memory_addr_t addr)
{
	return physic_memory->cells[addr];
}
