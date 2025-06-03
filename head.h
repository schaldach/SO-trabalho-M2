// IMPORTS
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdalign.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

// Usado para substituir o unsigned short e unsigned int 
typedef uint32_t u32; 
typedef uint16_t u16;

// 16 ou 32
#define logical_adress_bit_size 32

// páginas de 2KB a 256B para 16 bits, 4KB para 32 bits
#if logical_adress_bit_size == 16
    // 11 para 2048 (2KB), 10 para 1024 (1KB), 9 para 512 (512B), 8 para 256 (256B)
    #define page_offset_bit_size 11
    #define page_number_bit_size 5
    #define full_page_number_bit_size page_number_bit_size
    #define input_format "%hu\0" 
    typedef u16 input_type;
#else
    #define page_offset_bit_size 12
    #define page_number_bit_size 10
    #define full_page_number_bit_size page_number_bit_size*2
    #define input_format "%u\0"
    typedef u32 input_type;
#endif

// se será escrito em hexadecimal ou decimal
#define hex true

// o limite total para o número de frames seria 
// 244 para 32 bits (páginas de 4KB e 1 milhão de linhas)
// e 488 para 16 bits (páginas de 2KB)
#define max_frame_number 100

#define page_table_32b_number 1024
#define page_table_32b_row_number 1024
#define page_table_16b_row_number 32

#define tlb_row_number 16

#define MEMORY_LINE_SIZE 20
#define MEMORY_FILE "data_memory.txt"

#define head_print_size 5