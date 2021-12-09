#include "utilitariosAluno.h"
#include <stdlib.h>

Analise *inicializaAnalise()
{
    Analise *analise1;
    analise1 = (Analise *)malloc(sizeof(Analise));
    analise1->tempo = 0.0;
    analise1->comparacao = 0;
    analise1->transferenciaL = 0;
    analise1->transferenciaE = 0;
    return analise1;
}

void learq1(char *qualArquivo, int N_elementos, int p_flag)
{
    Aluno1 aux;
    char lixo[1];
    FILE *arquivoTexto;
    FILE *arquivoBin;
    arquivoTexto = fopen(qualArquivo, "r");
    arquivoBin = fopen("convBin.bin", "w+b");
    for (int c = 0; c < N_elementos; c++)
    {
        fscanf(arquivoTexto, "%lu %lf %s", &aux.matricula, &aux.nota, aux.estado);

        fread(lixo, 1, 1, arquivoTexto);
        fread(aux.cidade, 50, 1, arquivoTexto);
        aux.cidade[50] = '\0';
        // ignorando o proximo espaco
        fread(lixo, 1, 1, arquivoTexto);
        fread(aux.curso, 30, 1, arquivoTexto);
        aux.curso[30] = '\0';

        if(p_flag)
            printf("%08ld %05.1f %s %s %s\n", aux.matricula, aux.nota, aux.estado, aux.cidade, aux.curso);
        fwrite(&aux, sizeof(Aluno1), 1, arquivoBin);
        
    }
    if(p_flag) printf("\n\n");
    fclose(arquivoTexto);
    fclose(arquivoBin);
}

void fitas2txt(int n)
{
    char nome[30], aux[10];
    for (int i = 1; i <= n; i++)
    {
        strcpy(nome, "fitas/fita");
        sprintf(aux, "%d", i);
        //itoa(i, aux, 10);
        strcat(nome, aux);
        strcat(nome, ".bin");
    }
}

void toTxt(const char *arq, int p_flag)
{
    FILE *bin = fopen(arq, "rb");
    FILE *txt = fopen("saida.txt", "w+");
    if (bin == NULL || txt == NULL)
        return;
    Aluno1 alu;
    while (fread(&alu, sizeof(Aluno1), 1, bin) == 1){
        fprintf(txt, "%08ld %04.1f %3s %50s %30s\n", alu.matricula, alu.nota, alu.estado, alu.cidade, alu.curso);
        if(p_flag && alu.matricula > 0)
            printf("%08ld %05.1f %s %s %s\n", alu.matricula, alu.nota, alu.estado, alu.cidade, alu.curso);
    }
    fclose(bin);
    fclose(txt);
}

