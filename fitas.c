#include "fitas.h"

FILE** criar_fitas(int n, FILE* fitas[n*2]){
    char str[17];
    
    for(int i=0;i<n*2;i++){
        sprintf(str, "fitas/fita%d.bin", i);
        fitas[i] = fopen(str,"w+b");
    }
    return fitas;
}