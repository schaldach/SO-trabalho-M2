typedef struct {
    // aqui não temos o endereço lógico pois ele será o index da linha da tabela
    unsigned short physical_adress; // 16 bits 
    // unsigned int physical_adress; // 32 bits
    bool dirty_bit; // se foi modificado (acho)
    bool accessed_bit; // se foi acessado
    bool valid_bit; // se realmente aponta para uma página válida
} PAGE_TABLE_ROW;

PAGE_TABLE_ROW page_table[32] = {
    [0] = { .physical_adress=12, .dirty_bit=0, .accessed_bit=0, .valid_bit=1 },
    [1] = { .physical_adress=12, .dirty_bit=0, .accessed_bit=0, .valid_bit=1 },
    [2] = { .physical_adress=12, .dirty_bit=0, .accessed_bit=0, .valid_bit=1 },
    [3] = { .physical_adress=12, .dirty_bit=0, .accessed_bit=0, .valid_bit=1 },
    [4] = { .physical_adress=12, .dirty_bit=0, .accessed_bit=0, .valid_bit=1 },
    [5] = { .physical_adress=12, .dirty_bit=0, .accessed_bit=0, .valid_bit=0 },
    [6] = { .physical_adress=12, .dirty_bit=0, .accessed_bit=0, .valid_bit=0 },
};

void init_page_table_empty_rows(){
    for(int i=7; i<32; i++){
        page_table[i].physical_adress=0;
        page_table[i].dirty_bit=0;
        page_table[i].accessed_bit=0;
        page_table[i].valid_bit=1;
    }
};