typedef struct {
    // aqui não temos o endereço lógico pois ele será o index da linha da tabela
    // unsigned int physical_adress;
    unsigned short physical_adress;
    bool dirty_bit; // se foi modificado (acho)
    bool accessed_bit; // se foi acessado
    bool valid_bit; // se realmente aponta para uma página válida
} PAGE_TABLE_ROW;

function init_page_table_row(PAGE_TABLE_ROW* page_table, int n){
    page_table[n] = {.physical_adress=0, .dirty_bit=0, .accessed_bit=0, valid_bit=1 };
} 

PAGE_TABLE_ROW page_table[32] = {
    [0] = { .physical_adress=12, .dirty_bit=0, .accessed_bit=0, valid_bit=1 },
    [1] = { .physical_adress=12, .dirty_bit=0, .accessed_bit=0, valid_bit=1 },
    [2] = { .physical_adress=12, .dirty_bit=0, .accessed_bit=0, valid_bit=1 },
    [3] = { .physical_adress=12, .dirty_bit=0, .accessed_bit=0, valid_bit=1 },
    [4] = { .physical_adress=12, .dirty_bit=0, .accessed_bit=0, valid_bit=1 },
    [5] = { .physical_adress=12, .dirty_bit=0, .accessed_bit=0, valid_bit=1 },
    [6] = { .physical_adress=12, .dirty_bit=0, .accessed_bit=0, valid_bit=1 },
}

for(int i=7; i<32; i++){
    init_page_table_row(i);
}