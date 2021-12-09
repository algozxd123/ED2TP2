#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include "ibqs.h"
#include "qSortExt.h"
#include "intercalaSub.h"

int main(int argc, char** argv){

    /**
     * Método:
     * 1 = intercalação balanceada de vários caminhos (2f)
     * 2 = intercalação balanceada de vários caminhos (2f) utilizando seleção por substituição
     * 3 = quicksort externo
     */
    int metodo = strtol(argv[1], NULL, 10);

    //Quantidade
    int n_itens = strtol(argv[2], NULL, 10);
    
    /**
     * Situação:
     * 1 = ascendente
     * 2 = descendente
     * 3 = aleatorio
     */
    int situacao = strtol(argv[3], NULL, 10);

    char filename[18];
    if(situacao == 1){
        strcpy(filename, "arquivo_asc.txt");
    }
    if(situacao == 2){
        strcpy(filename, "arquivo_desc.txt");
    }
    if(situacao == 3){
        strcpy(filename, "arquivo_rand.txt");
    }

    //Flag opcional -P
    int p_flag = 0;
    if(argc == 5 && !strcmp(argv[4], "-P")) p_flag = 1;

    //Variáveis de medidas de performance
    int n_leituras = 0;
    int n_escritas = 0;
    int n_comparacoes = 0;
    clock_t start, end;
    double tempo_execucao;

    int resultado_flag = 0;
    
    start = clock();
    if(metodo == 1){
        resultado_flag = ibqs(n_itens, filename, &n_leituras, &n_escritas, &n_comparacoes, p_flag);
    }else if(metodo == 2){
        resultado_flag = intercalaSub(n_itens, filename, &n_leituras, &n_escritas, &n_comparacoes, p_flag);
    }else if(metodo == 3){
        resultado_flag = QuickSortExternoPrograma(n_itens, filename, &n_leituras, &n_escritas, &n_comparacoes, p_flag);
    }

    end = clock();
    tempo_execucao = ((double) (end - start)) / CLOCKS_PER_SEC;

    if(resultado_flag){
        printf("Numero de leituras: %d\n",n_leituras);
        printf("Numero de escritas: %d\n",n_escritas);
        printf("Numero de comparacoes: %d\n",n_comparacoes);
        printf("Tempo de execucao: %lf s\n",tempo_execucao);
    }
    
    return 0;
}