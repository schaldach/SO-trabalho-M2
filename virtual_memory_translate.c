#include "head.h"
#include "page_table.c"
#include "tlb.c"

int main(){
    TLB_ROW tlb[tlb_row_number];
    init_tlb_rows(tlb);

    // não da para usar define pois têm que ser "unsigned" para operações com bits
    // quantos deslocamentos existem em uma página
    u16 page_offset_size = 1<<page_offset_bit_size;
    // quantos números de página existem
    u16 page_number_size = 1<<page_number_bit_size;
    // quantos números de páginas "totais" (considerando interna e externa) existem
    u32 full_page_number_size = 1<<full_page_number_bit_size;
    
    input_type input;

    // 16 bits
    PAGE_TABLE_ROW page_table_16b[page_table_16b_row_number];
    init_page_table_16b_rows(page_table_16b);

    // 32 bits
    OUTER_PAGE_TABLE_ROW outer_page_table[page_table_32b_number];
    init_page_table_32b_rows(outer_page_table);

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

        // traduzindo o endereço lógico com operações binárias
        u16 page_offset = input & (page_offset_size-1);
        u32 full_page_number = input >> page_offset_bit_size;
            full_page_number = full_page_number & (full_page_number_size-1);
        // para 16 bits, é apenas o page_number,  e para 32 bits, é o page_number junto do outer_page_number
        // para ambos, é o endereço que será salvo na TLB

        u16 page_number = full_page_number & (page_number_size-1);
        u16 outer_page_number = full_page_number >> (page_number_bit_size);

        u32 frame_number;

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
                page_table_16b[page_number].accessed_bit = true;
                bool valid_bit = page_table_16b[page_number].valid_bit;
                if(valid_bit == 0){
                    printf("Page Fault\n");
                    page_table_16b[page_number].physical_adress = 105;
                    page_table_16b[page_number].valid_bit = true;
                    printf("Page swapped into memory\n");
                }
                else{
                    printf("Page hit\n");
                }
                frame_number = page_table_16b[page_number].physical_adress;
            }
            //32 bits
            else{
                if(outer_page_table[outer_page_number].page_table_pointer == NULL){
                    alocate_page_table(outer_page_table, outer_page_number);
                }
                PAGE_TABLE_ROW* page_table_32b = outer_page_table[outer_page_number].page_table_pointer;
                page_table_32b[page_number].accessed_bit = true;
                bool valid_bit = page_table_32b[page_number].valid_bit;
                if(valid_bit == 0){
                    printf("Page Fault\n");
                    page_table_32b[page_number].physical_adress = 105;
                    page_table_32b[page_number].valid_bit = true;
                    printf("Page swapped into memory\n");
                }
                else{
                    printf("Page hit\n");
                }
                frame_number = page_table_32b[page_number].physical_adress;
            }
            replace_tlb(tlb, full_page_number, frame_number);
        }
        else{
            printf("TLB hit\n");
        }

        u32 file_physical_adress = frame_number*page_offset_size + page_offset;
        
        // lendo a posição do arquivo (endereço físico)
        FILE *fptr = fopen(MEMORY_FILE, "r");
        char currentLine[MEMORY_LINE_SIZE];
        u16 result; 
        u32 i = 0;

        while(fgets(currentLine, MEMORY_LINE_SIZE, fptr)){
            if(i == file_physical_adress){
                result = atoi(currentLine);
                break;
            }
            i++;
        }
        fclose(fptr);

        // Informações gerais da busca
        printf("\n-> número da página: %u\n-> número do quadro: %d\n-> deslocamento da página: %hu\n-> linha do arquivo (início = 0): %u\n-> valor lido na memória: %d\n", 
            full_page_number, frame_number, page_offset, file_physical_adress, result);

        { //Logica para sair do loop
            char c[1];
            printf("\nDigite 'q' se desejas parar o programa: ");
            scanf("%s",c); //"%d",
            
            if(c[0] == 'q'){
                printf("quit\n");
                break;
            }
        }
    }

   return 0;
}