#ifndef INTERCALACAO_H
#define INTERCALACAO_H

#include <stdio.h>
#include <stdlib.h>
#include "fitas.h"
#include "qsin.h"

typedef struct {
    Aluno bloco[20];
    int fonteFita[20];
}Memoria;


void intercalacao(int qte, FILE **fitas, Aluno *mem, int* n_leituras, int* n_escrita, int* n_comparacoes, int p_flag);
int fitaIndisponivel(FILE *fita);
void colocarnaFita(Aluno x, FILE *fita);
Memoria shellsort(Memoria v, int n);
void bintoTxt(int qte, FILE *fita, char *nome, int p_flag);
int int_pow(int base, int exp);
int pegaMenorFita(FILE **fitas, int QteFitas, int u);

#endif