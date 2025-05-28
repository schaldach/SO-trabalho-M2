#include "head.h"
#include "page_table.c"
#include "tlb.c"

int main(){
    TLB_ROW tlb[tlb_row_number];
    init_tlb_rows(tlb);
    print_tlb(tlb);

    // não da para usar define pois têm que ser "unsigned" para operações com bits
    // quantos deslocamentos existem em uma página
    unsigned short page_offset_size = 1<<page_offset_bit_size;
    // quantos números de página existem
    unsigned short page_number_size = 1<<page_number_bit_size;
    
    // 16 bits
    PAGE_TABLE_ROW page_table_16b[page_table_16b_row_number];
    if(logical_adress_bit_size == 16){
        init_page_table_16b_rows(page_table_16b);
        print_page_table_16b(page_table_16b);
    }
    // unsigned short input;

    // 32 bits
    PAGE_TABLE_ROW* page_table_32b[page_table_32b_number];
    OUTER_PAGE_TABLE_ROW outer_page_table[page_table_32b_number];
    if(logical_adress_bit_size == 32){
        init_page_table_32b_rows(page_table_32b, outer_page_table);
        print_page_table_32b(page_table_32b, outer_page_table);
    } 
    unsigned int input;

   // pegando input do console
   printf("Digite o endereço lógico: \n");
   char* format;
   if(hex) format = "%x\0";
   else format = input_format;
   scanf(format, &input);
   printf("\n");

    // traduzindo o número com operações binárias
    unsigned short page_offset = input & (page_offset_size-1);
    unsigned short page_number = input >> page_offset_bit_size;
    if(logical_adress_bit_size == 32){
        page_number = page_number & (page_number_size-1);
    }
    unsigned short outer_page_number = input >> (page_number_bit_size+page_offset_bit_size);

    unsigned int frame_number;

    // buscando na TLB
    bool tlb_hit = false;
    for(int i=0; i<tlb_row_number; i++){
        if(tlb[i].virtual_adress == page_number){
            frame_number = tlb[i].physical_adress;
            tlb_hit = true;
        }
    }

    // se não foi achado na TLB, buscar na page_table
    if(!tlb_hit){
        printf("TLB Miss\n");

        // 16 bits
        if(logical_adress_bit_size == 16){
            bool valid_bit = page_table_16b[page_number].valid_bit;
            if(valid_bit == 0){
                printf("Page Fault\n");
                page_table_16b[page_number].physical_adress = 100;
                printf("Page swapped into memory\n");
            }
            else{
                printf("Page hit\n");
            }
            frame_number = page_table_16b[page_number].physical_adress;
        }
        //32 bits
        else{
            unsigned short page_table_index = outer_page_table[outer_page_number].page_table_index;
            bool valid_bit = page_table_32b[page_table_index][page_number].valid_bit;
            if(valid_bit == 0){
                printf("Page Fault\n");
                page_table_32b[page_table_index][page_number].physical_adress = 100;
                printf("Page swapped into memory\n");
            }
            else{
                printf("Page hit\n");
            }
            frame_number = page_table_32b[page_table_index][page_number].physical_adress;
        }
        replace_tlb(tlb, page_number, frame_number);
    }
    else{
        printf("TLB hit\n");
    }

    unsigned int file_physical_adress = frame_number*page_offset_size + page_offset;
    
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

    printf(" número da página: %u\n número do quadro: %d\n deslocamento da página: %hu\n linha do arquivo: %u\n valor lido na memória: %d\n", 
        page_number, frame_number, page_offset, file_physical_adress, result);


   return 0;
}