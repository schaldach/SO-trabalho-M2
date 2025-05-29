#include "head.h"

typedef struct {
    // aqui não temos o endereço lógico pois ele será o index da linha da tabela
    unsigned int physical_adress;
    bool dirty_bit; // se foi modificado (acho)
    bool accessed_bit; // se foi acessado
    bool valid_bit; // se realmente aponta para uma página válida
} PAGE_TABLE_ROW;

typedef struct {
    PAGE_TABLE_ROW* page_table_pointer;
} OUTER_PAGE_TABLE_ROW;

void init_page_table_16b_rows(
    PAGE_TABLE_ROW page_table_16b[page_table_16b_row_number]
){
    for(int i=0; i<page_table_16b_row_number; i++){
        int valid_bit = (i<20) ? true : false;

        page_table_16b[i].physical_adress = i+3;
        page_table_16b[i].dirty_bit = false;
        page_table_16b[i].accessed_bit = false;
        page_table_16b[i].valid_bit = valid_bit;
    }
};

void print_page_table_16b(
    PAGE_TABLE_ROW page_table_16b[page_table_16b_row_number]
){
    printf("Page Table:\n");
    for(int i=0;i<page_table_16b_row_number;i++){
        printf("%2d - end. físico: %12u, bit acesso: %d, bit sujo: %d, bit válido: %d\n", i, page_table_16b[i].physical_adress, page_table_16b[i].accessed_bit, page_table_16b[i].dirty_bit, page_table_16b[i].valid_bit);
    }
    printf("\n");
};

void print_page_table_32b(
    OUTER_PAGE_TABLE_ROW outer_page_table[page_table_32b_number]
){
    for(int i=0; i<page_table_32b_number; i++){
        if(outer_page_table[i].page_table_pointer != NULL){
            PAGE_TABLE_ROW* page_table_32b = outer_page_table[i].page_table_pointer;
            printf("Page Table %d (%d)\n", i, head_print_size);
            for(int j=0; j<head_print_size; j++){
                printf("%4d - end. físico: %12u, bit acesso: %d, bit sujo: %d, bit válido: %d\n", i, page_table_32b[j].physical_adress, page_table_32b[j].accessed_bit, page_table_32b[j].dirty_bit, page_table_32b[j].valid_bit);
            }
            printf("\n");
        }
    }
    printf("Outer Page Table (%d):\n", head_print_size);
    for(int i=0;i<head_print_size;i++){
        printf("%2d - ponteiro tabela de páginas: %p\n", i, outer_page_table[i].page_table_pointer);
    }
    printf("\n");
};

void dealocate_page_tables(OUTER_PAGE_TABLE_ROW outer_page_table[page_table_32b_number]){
    for(int i=0;i<page_table_32b_number; i++){
        if(outer_page_table[i].page_table_pointer != NULL){
            free(outer_page_table[i].page_table_pointer);
        }
    }
};

// Necessário pois não conseguimos armazenar 1024 tabelas de página,
// então vamos simular como o computador faria, trazendo a tabela interior da memória
// pois apenas a tabela exterior fica na memória principal
void alocate_page_table(OUTER_PAGE_TABLE_ROW outer_page_table[page_table_32b_number], unsigned short index){
    // criar nova tabela
    PAGE_TABLE_ROW *ptr = (PAGE_TABLE_ROW *)malloc(sizeof(PAGE_TABLE_ROW) * page_table_32b_row_number);
    if(ptr == NULL){
        printf("Memory Allocation failed\n");
        printf("Dealocating other pages\n");
        dealocate_page_tables(outer_page_table);
        alocate_page_table(outer_page_table, index); // tentando novamente
        return;
    }
    else{
        printf("Memory Allocation successful\n");
    }

    srand(index);
    //popular tabela
    for(int i=0; i<page_table_32b_row_number; i++){
        bool valid_bit = (i<200) ? true:false;

        ptr[i].physical_adress = rand()%max_frame_number;
        ptr[i].dirty_bit = false;
        ptr[i].accessed_bit = false;
        ptr[i].valid_bit = valid_bit;
    }

    outer_page_table[index].page_table_pointer = ptr;
};

void init_page_table_32b_rows(
    OUTER_PAGE_TABLE_ROW outer_page_table[page_table_32b_number]
){
    for(int i=0; i<page_table_32b_number; i++){
        outer_page_table[i].page_table_pointer = NULL;
    }
    alocate_page_table(outer_page_table, 0);
};