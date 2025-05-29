#include "head.h"
#include "page_table.c"
#include "tlb.c"

int main(){
    TLB_ROW tlb[tlb_row_number];
    init_tlb_rows(tlb);

    // não da para usar define pois têm que ser "unsigned" para operações com bits
    // quantos deslocamentos existem em uma página
    unsigned short page_offset_size = 1<<page_offset_bit_size;
    // quantos números de página existem
    unsigned short page_number_size = 1<<page_number_bit_size;
    
    // 16 bits
    PAGE_TABLE_ROW page_table_16b[page_table_16b_row_number];
    init_page_table_16b_rows(page_table_16b);
    // unsigned short input;

    // 32 bits
    OUTER_PAGE_TABLE_ROW outer_page_table[page_table_32b_number];
    init_page_table_32b_rows(outer_page_table);
    unsigned int input;

    while(true){
        printf("----------\n");
        print_tlb(tlb);
        if(logical_adress_bit_size == 16){
            print_page_table_16b(page_table_16b);
        }
        else{
            print_page_table_32b(outer_page_table);
        }
        printf("----------\n");

        // pegando input do console
        printf("Digite o endereço lógico: \n");
        char* format;
        if(hex) format = "%x\0";
        else format = input_format;
        scanf(format, &input);
        printf("\n");

        // traduzindo o número com operações binárias
        unsigned short page_offset = input & (page_offset_size-1);
        // para 16 bits, é apenas o page_number, e para 32 bits, é o page_number junto do outer_page_number
        unsigned int full_page_number = input >> page_offset_bit_size;

        unsigned short page_number = full_page_number & (page_number_size-1);
        unsigned short outer_page_number = full_page_number >> (page_number_bit_size);

        unsigned int frame_number;

        // buscando na TLB
        bool tlb_hit = false;
        for(int i=0; i<tlb_row_number; i++){
            if(full_page_number == tlb[i].virtual_adress){
                frame_number = tlb[i].physical_adress;
                tlb[i].accessed_bit = 1;
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
                    page_table_16b[page_number].physical_adress = 105;
                    page_table_16b[page_number].valid_bit = true;
                    page_table_16b[page_number].accessed_bit = true;
                    printf("Page swapped into memory\n");
                }
                else{
                    printf("Page hit\n");
                }
                frame_number = page_table_16b[page_number].physical_adress;
            }
            //32 bits
            else{
                alocate_page_table(outer_page_table, outer_page_number);
                PAGE_TABLE_ROW* page_table_32b = outer_page_table[outer_page_number].page_table_pointer;
                bool valid_bit = page_table_32b[page_number].valid_bit;
                if(valid_bit == 0){
                    printf("Page Fault\n");
                    page_table_32b[page_number].physical_adress = 105;
                    page_table_32b[page_number].valid_bit = true;
                    page_table_32b[page_number].accessed_bit = true;
                    printf("Page swapped into memory\n");
                }
                else{
                    printf("Page hit\n");
                }
                frame_number = page_table_32b[page_number].physical_adress;
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

        printf("\n-> número da página: %u\n-> número do quadro: %d\n-> deslocamento da página: %hu\n-> linha do arquivo: %u\n-> valor lido na memória: %d\n", 
            page_number, frame_number, page_offset, file_physical_adress, result);

        int l;
        printf("\nDigite um inteiro para continuar:\n");
        scanf("%d", &l);
    }

   return 0;
}