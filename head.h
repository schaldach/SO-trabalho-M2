// IMPORTS
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

// MODIFICÁVEIS
// 16 ou 32
#define logical_adress_bit_size 32
#define hex true

// CONSTANTES
// páginas de 2KB para 16 bits, 4KB para 32 bits
#if logical_adress_bit_size == 16
    #define page_offset_bit_size 11
    #define page_number_bit_size 5
    #define input_format "%hu\0" 
#else
    #define page_offset_bit_size 12
    #define page_number_bit_size 10
    #define input_format "%u\0"
#endif

#define max_frame_number 100
// o limite total seria aproximadamente 244 para 32 bits (páginas de 4KB e 1 milhão de linhas)
// e 488 para 16 bits (páginas de 2KB)

#define page_table_32b_number 1024
#define page_table_32b_row_number 1024
#define page_table_16b_row_number 32

#define tlb_row_number 16

#define MEMORY_LINE_SIZE 20
#define MEMORY_FILE "data_memory.txt"