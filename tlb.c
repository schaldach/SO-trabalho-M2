typedef struct {
    int virtual_adress;
    int physical_adress;
} TLB_ROW;

TLB_ROW tlb[16] = {
    [0] = { .virtual_adress=2, .physical_adress=12 },
    [1] = { .virtual_adress=2, .physical_adress=12 },
    [2] = { .virtual_adress=2, .physical_adress=12 },
    [3] = { .virtual_adress=2, .physical_adress=12 },
    [4] = { .virtual_adress=2, .physical_adress=12 }
};

void init_tlb_empty_rows(){
    for(int i=5; i<16; i++){
        tlb[i].virtual_adress=0;
        tlb[i].physical_adress=0;
    }
};