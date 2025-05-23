// IMPORTS
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "page_table.c"
#include "tlb.c"

// MODIFICÁVEIS
#define MMU_CONSTANT 1;
#define logical_adress_bit_size 32
#define page_bit_size 12 

// CONSTANTES
#define page_size 1<<page_bit_size // 2^page_bit_size
#define MEMORY_LINE_SIZE 20
#define MEMORY_FILE "data_memory.txt"

// cada número da memória na verdade representa apenas 1 byte, não um número (int ou short) em si
// o tamanho das páginas "256B, 1kB, 4kB" se referem a byte (B) e não bits (b)

int main(){
    init_page_table_empty_rows();
    init_tlb_empty_rows();

//    unsigned short input; // 16 bits 
//    char* format = "%hu";
   unsigned int input; // 32 bits
   char* format = "%u";

   // pegando input do console
   printf("Digite o endereço lógico: \n");
   scanf(format, &input);
   printf(format, input);
   printf("\n");

    // traduzindo o número em decimal
    unsigned int page_offset = input & (page_size-1);
    unsigned int page_number = input - page_offset;

    // lendo a posição do arquivo
    FILE *fptr = fopen(MEMORY_FILE, "r");
    char currentLine[MEMORY_LINE_SIZE];
    int result, i=0;
    while(fgets(currentLine, MEMORY_LINE_SIZE, fptr)){
        int physical_adress = page_number*(1<<12) + page_offset;

        physical_adress += MMU_CONSTANT;
        if(i == physical_adress){
            result = atoi(currentLine);
            break;
        }
        i++;
    }
    fclose(fptr);

    printf(" número da página:%u\n deslocamento da página:%hu\n valor lido na memória:%d\n", 
        page_number, page_offset, result);


   return 0;
}