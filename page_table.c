#include "head.h"

typedef struct {
    // aqui não temos o endereço lógico pois ele será o index da linha da tabela
    unsigned int physical_adress;
    bool dirty_bit; // se foi modificado (acho)
    bool accessed_bit; // se foi acessado
    bool valid_bit; // se realmente aponta para uma página válida
} PAGE_TABLE_ROW;

typedef struct {
    unsigned short page_table_index;
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
    PAGE_TABLE_ROW* page_table_32b[page_table_32b_number], 
    OUTER_PAGE_TABLE_ROW outer_page_table[page_table_32b_number]
){
    for(int i=0; i<page_table_32b_number; i++){
        if(page_table_32b[i] != NULL){
            printf("Page Table %d (10)\n", i);
            for(int j=0; j<10; j++){
                printf("%4d - end. físico: %12u, bit acesso: %d, bit sujo: %d, bit válido: %d\n", i, page_table_32b[i][j].physical_adress, page_table_32b[i][j].accessed_bit, page_table_32b[i][j].dirty_bit, page_table_32b[i][j].valid_bit);
            }
            printf("\n");
        }
    }
    printf("Outer Page Table (10):\n");
    for(int i=0;i<10;i++){
        printf("%2d - index tabela de páginas: %4u\n", i, outer_page_table[i].page_table_index);
    }
    printf("\n");
};

void dealocate_page_tables(PAGE_TABLE_ROW* page_table_32b[page_table_32b_number]){
    for(int i=0;i<page_table_32b_number; i++){
        if(page_table_32b[i] != NULL){
            free(page_table_32b[i]);
        }
    }
};

// Necessário pois não conseguimos armazenar 1024 tabelas de página,
// então vamos simular como o computador faria, trazendo a tabela interior da memória
// pois apenas a tabela exterior fica na memória principal
void alocate_page_table(PAGE_TABLE_ROW* page_table_32b[page_table_32b_number], unsigned short index){
    // criar nova tabela
    PAGE_TABLE_ROW *ptr = (PAGE_TABLE_ROW *)malloc(sizeof(PAGE_TABLE_ROW) * page_table_32b_row_number);
    if(ptr == NULL){
        printf("Memory Allocation failed\n");
        printf("Dealocating other pages\n");
        dealocate_page_tables(page_table_32b);
        alocate_page_table(page_table_32b, index); // tentando novamente
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

    page_table_32b[index] = ptr;
};

void init_page_table_32b_rows(
    PAGE_TABLE_ROW* page_table_32b[page_table_32b_number], 
    OUTER_PAGE_TABLE_ROW outer_page_table[page_table_32b_number]
){
    for(int i=0; i<page_table_32b_number; i++){
        outer_page_table[i].page_table_index = i+2;
        page_table_32b[i] = NULL;
    }
    alocate_page_table(page_table_32b, 0);
};