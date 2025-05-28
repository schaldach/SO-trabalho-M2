typedef struct {
    // aqui não temos o endereço lógico pois ele será o index da linha da tabela
    unsigned int physical_adress;
    bool dirty_bit; // se foi modificado (acho)
    bool accessed_bit; // se foi acessado
    bool valid_bit; // se realmente aponta para uma página válida
} PAGE_TABLE_ROW;

typdef struct {
    PAGE_TABLE_ROW page_table[32];
} PAGE_TABLE_16B

typdef struct {
    // 1024 = 2^10 (10 bits de tamanho)
    PAGE_TABLE_ROW page_table[1024][1024];
} PAGE_TABLE_32B

typedef struct {
    unsigned short page_table_index;
} OUTER_PAGE_TABLE_ROW;

typdef struct {
    OUTER_PAGE_TABLE_ROW outer_page_table[1024];
} OUTER_PAGE_TABLE

void init_page_table_16b_rows(PAGE_TABLE_16B *page_table_16b){
    for(int i=0; i<32; i++){
        int valid_bit;
        (i<16) ? valid_bit = 1: valid_bit = 0;

        page_table_16b[i].physical_adress = i+3;
        page_table_16b[i].dirty_bit = 0;
        page_table_16b[i].accessed_bit = 0;
        page_table_16b[i].valid_bit = valid_bit;
    }
}

void init_page_table_32b_rows(PAGE_TABLE_32B *page_table_32b, OUTER_PAGE_TABLE *outer_page_table){
    // 32 bits
    for(int i=0; i<1024; i++){
        // outer table
        outer_page_table[i].page_table_index = i+2;

        // inner table
        for(int j=0; j<1024; j++){
            int valid_bit;
            (i<512) ? valid_bit = 1: valid_bit = 0;

            page_table_32b[i][j].physical_adress = i+4;
            page_table_32b[i][j].dirty_bit = 0;
            page_table_32b[i][j].accessed_bit = 0;
            page_table_32b[i][j].valid_bit = valid_bit;
        }
    }
};