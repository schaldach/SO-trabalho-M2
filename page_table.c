#define page_table_32b_number 10 // deveria ser 1024 mas estoura a memória
// será que deveria também ser simulado o fato de que a page table interior é trazida da memória?
// ou podemos apenas usar menos tabelas de páginas?
#define page_table_32b_row_number 1024
#define page_table_16b_row_number 32

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

void init_page_table_32b_rows(
    PAGE_TABLE_ROW page_table_32b[page_table_32b_number][page_table_32b_row_number], 
    OUTER_PAGE_TABLE_ROW outer_page_table[page_table_32b_number]
){
    // 32 bits
    for(int i=0; i<page_table_32b_number; i++){
        // outer table
        outer_page_table[i].page_table_index = i+2;

        // inner table
        for(int j=0; j<page_table_32b_row_number; j++){
            bool valid_bit = (j<200) ? true : false;

            page_table_32b[i][j].physical_adress = i+4;
            page_table_32b[i][j].dirty_bit = false;
            page_table_32b[i][j].accessed_bit = false;
            page_table_32b[i][j].valid_bit = valid_bit;
        }
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
    PAGE_TABLE_ROW page_table_32b[page_table_32b_number][page_table_32b_row_number], 
    OUTER_PAGE_TABLE_ROW outer_page_table[page_table_32b_number]
){
    printf("Page Table 0 (10):\n");
    for(int i=0;i<10;i++){
        printf("%4d - end. físico: %12u, bit acesso: %d, bit sujo: %d, bit válido: %d\n", i, page_table_32b[0][i].physical_adress, page_table_32b[0][i].accessed_bit, page_table_32b[0][i].dirty_bit, page_table_32b[0][i].valid_bit);
    }
    printf("\n");
    printf("Outer Page Table (10):\n");
    for(int i=0;i<10;i++){
        printf("%2d - index tabela de páginas: %4u\n", i, outer_page_table[i].page_table_index);
    }
    printf("\n");
};