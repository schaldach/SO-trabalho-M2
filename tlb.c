#include "head.h"

typedef struct {
    unsigned int virtual_adress;
    unsigned int physical_adress;
    bool accessed_bit;
} TLB_ROW;

void init_tlb_rows(TLB_ROW tlb[tlb_row_number]){
    for(int i=0; i<tlb_row_number; i++){
        bool accessed_bit = (i<8) ? true : false;

        tlb[i].accessed_bit = accessed_bit;
        tlb[i].virtual_adress = i;
        tlb[i].physical_adress = i+1;
    }
};

void replace_tlb(TLB_ROW tlb[tlb_row_number], unsigned int virtual_adress, unsigned int physical_adress){
    // implementando LRU com segunda chance
    bool replaced = false;
    for(int i=0; i<tlb_row_number; i++){
        if(tlb[i].accessed_bit){
            tlb[i].accessed_bit = false;
        }
        else if(!replaced){
            tlb[i].virtual_adress = virtual_adress;
            tlb[i].physical_adress = physical_adress;
            tlb[i].accessed_bit = true;
            replaced = true;
        }
    }

    // se nenhuma linha foi substituída, substituir a primeira
    if(!replaced){
        tlb[0].virtual_adress = virtual_adress;
        tlb[0].physical_adress = physical_adress;
        tlb[0].accessed_bit = true;
    }
};

void print_tlb(TLB_ROW tlb[tlb_row_number]){
    printf("TLB:\n");
    for(int i=0;i<tlb_row_number;i++){
        printf("%2d - end. lógico: %6hu, end. físico: %12u, bit acesso: %d\n", i, tlb[i].virtual_adress, tlb[i].physical_adress, tlb[i].accessed_bit);
    }
    printf("\n");
};