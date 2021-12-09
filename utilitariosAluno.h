#ifndef UTILITARIOSALUNO_H
#define UTILITARIOSALUNO_H
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct analise Analise;

struct analise
{
    long double tempo;
    long long int comparacao;
    long long int transferenciaL;
    long long int transferenciaE;
};

typedef struct alu Aluno1;

struct alu
{
    long int matricula;
    double nota;
    char estado[3];
    char cidade[51];
    char curso[31];
};

void learq1(char *qualArquivo, int N_elementos, int p_flag);
Analise *inicializaAnalise();
void fitas2txt(int n);
void toTxt(const char *arq, int p_flag);

#endif 