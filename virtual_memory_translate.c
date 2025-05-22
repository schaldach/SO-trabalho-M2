#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

const char* MEMORY_FILE = "data_memory.txt";
const int MEMORY_LINE_SIZE = 20;
const int MMU_CONSTANT = 1;

typedef struct {
    int virtual_adress;
    int physical_adress;
} TLB_ROW;

typedef struct {
    TLB_ROW rows[16];
} TLB;

typedef struct {
    int virtual_adress;
    int physical_adress;
    bool dirty;
    bool accessed;
    bool valid;
} PAGE_TABLE_ROW;

typedef struct {
    PAGE_TABLE_ROW rows[32];
} PAGE_TABLE;

int main(){
    TLB tlb;
    PAGE_TABLE page_table;

//    unsigned short input; // 16 bits 
//    char* format = "%hu";
   unsigned int input; // 32 bits
   char* format = "%u";

   printf("Digite o endereço lógico: \n");
   scanf(format, &input);
   printf(format, input);
   printf("\n");

    // lendo o número em decimal
    unsigned int page_number = input / (1<<12);
    unsigned int page_offset = input % (1<<12);

    // lendo a posição do arquivo
    FILE *fptr = fopen(MEMORY_FILE, "r");
    char currentLine[MEMORY_LINE_SIZE];
    int result, i=0;
    while(fgets(currentLine, MEMORY_LINE_SIZE, fptr)){
        // não entendi como o endereço lógico se traduz no endereço físico! irei fazer por enquanto
        // como endereço lógico + 1 = endereço físico (é como eu entendi que funciona o MMU)
        // por enquanto TLB e PAGE_TABLE não tão sendo usadas, mas acredito que seria aqui, para a tradução
        if(i == page_number*(1<<12) + page_offset + MMU_CONSTANT){
            result = atoi(currentLine);
            break;
        }
        i++;
    }
    fclose(fptr);

    printf("número da página:%u\n deslocamento da página:%hu\n valor lido na memória:%d\n", 
        page_number, page_offset, result);


   return 0;
}