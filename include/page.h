#ifndef PAGE_H
#define PAGE_H

#include<stdint.h>
#include<stdbool.h>

#include"physic_memory.h"

#define NIL 0

#define CALC_PAGE_NUM(addr, low_bit_length) (page_num_size_t)(addr >> low_bit_length)

// ページサイズ
typedef uint16_t page_size_t;

// ページ数
typedef uint8_t page_num_size_t;

// ページエントリ
typedef struct {
	memory_addr_t frame_addr; // 物理メモリのフレームアドレス
	uint8_t exist_bit:     1;
	uint8_t available_bit: 1;
	uint8_t changed_bit:   1;
} page_entry_t;

// ページテーブル
typedef struct {
	page_entry_t *entries;
} page_table_t;

page_table_t *init_page_table(page_num_size_t page_nums);

// ページフォルト発生時の情報
typedef struct {
	memory_addr_t fault_addr;
	uint8_t low_bit_length;
	page_size_t page_size;
} page_fault_info_t;

#endif
