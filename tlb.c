typedef struct {
    unsigned int virtual_adress;
    unsigned int physical_adress;
} TLB_ROW;

typedef struct{
    TLB_ROW tlb[16];
} TLB;

void init_tlb_rows(TLB *tlb){
    for(int i=0; i<16; i++){
        tlb[i].virtual_adress = i;
        tlb[i].physical_adress = i+1;
    }
};