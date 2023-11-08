#include<stdlib.h>

#include"page.h"

static void init_page_entry(page_entry_t *entry) {
	entry->frame_addr = NIL;
	entry->exist_bit = 0;
	entry->available_bit = 0;
	entry->changed_bit = 0;
}

page_table_t *init_page_table(page_num_size_t page_nums)
{
	int i;
	page_table_t *table;
	table = (page_table_t *)malloc(sizeof(page_table_t));
	table->entries = (page_entry_t *)malloc(sizeof(page_entry_t) * page_nums);
	for (i = 0; i < page_nums; i++) {
		init_page_entry(&(table->entries[i]));
	}
	return table;
}
