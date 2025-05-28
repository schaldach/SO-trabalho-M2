// IMPORTS
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "page_table.c"
#include "tlb.c"

// MODIFICÁVEIS
// 16 ou 32
#define logical_adress_bit_size 32

// CONSTANTES

// páginas de 2KB para 16 bits, 4KB para 32 bits
#if logical_adress_bit_size == 16
    #define page_bit_size 11
    #define input_format "%hu" 
#else
    #define page_bit_size 12
    #define input_format "%u" 
#endif

#define page_size 1<<page_bit_size // 2^page_bit_size
#define MEMORY_LINE_SIZE 20
#define MEMORY_FILE "data_memory.txt"

int main(){
    TLB tlb;

    // 16 bits
    PAGE_TABLE_16B page_table_16b;
    init_page_table_16b_rows(page_table_16b);
    unsigned short input;
    // ----

    // 32 bits
    PAGE_TABLE_32B page_table_32b;
    OUTER_PAGE_TABLE outer_page_table;
    init_page_table_32b_rows(page_table_32b, outer_page_table);
    unsigned int input;
    // ----

   // pegando input do console
   printf("Digite o endereço lógico: \n");
   scanf(format, &input);
   printf(format, input);
   printf("\n");

    // traduzindo o número em decimal
    unsigned short page_offset = input & (page_size-1);
    unsigned short page_number = input >> page_bit_size;
    if(logical_adress_bit_size == 32){
        page_number = page_number & ((1<<10)-1)
    }
    unsigned short outer_page_number = input >> 22;

    unsigned int frame_number;

    // buscando na TLB
    bool tlb_hit = false;
    for(int i=0; i<32; i++){
        if(tlb[i].virtual_adress == page_number){
            frame_number = tlb[i].physical_adress;
            tlb_hit = true;
        }
    }
    // se não foi achado na TLB, buscar na page_table
    if(tlb_hit = false){
        printf("TLB Miss\n");

        // 16 bits
        if(logical_adress_bit_size == 16){
            frame_number = page_table_16b[i].physical_adress;
            valid_bit = page_table_32b[page_table_index][i].valid_bit;
            if(valid_bit == 0){
                printf("Page Fault\n");
                page_table_16b[i].physical_adress = 100;
                printf("Page swapped into memory\n");
            }
            else{
                printf("Page hit\n");
            }
        }
        //32 bits
        else{
            unsigned short page_table_index = outer_page_table[page_table_index].page_table_index;
            valid_bit = page_table_32b[page_table_index][i].valid_bit;
            if(valid_bit == 0){
                printf("Page Fault\n");
                page_table_32b[page_table_index][i].physical_adress = 100;
                printf("Page swapped into memory\n");
            }
            else{
                printf("Page hit\n");
            }
            frame_number = page_table_32b[page_table_index][i].physical_adress;
        }
    }

    unsigned int file_physical_adress = frame_number*(1<<12) + page_offset;
    
    // lendo a posição do arquivo (endereço físico)
    FILE *fptr = fopen(MEMORY_FILE, "r");
    char currentLine[MEMORY_LINE_SIZE];
    int result, i=0;

    while(fgets(currentLine, MEMORY_LINE_SIZE, fptr)){
        if(i == file_physical_adress){
            result = atoi(currentLine);
            break;
        }
        i++;
    }
    fclose(fptr);

    printf(" número da página:%u\n número do quadro:%d\n deslocamento da página:%hu\n valor lido na memória:%d\n", 
        page_number, frame_number, page_offset, result);


   return 0;
}