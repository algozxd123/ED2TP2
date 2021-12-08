#ifndef INTERCALASUB_H
#define INTERCALASUB_H
#define NFITAS 20
#define TAMMEM NFITAS / 2
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "utilitariosAluno.h"

typedef struct doheap doHeap;
void fitas2txt(int n);
void heapRefaz(doHeap *v, int esq, int dir, Analise *analise1);
void heapConstroi(doHeap *v, int n, Analise *analise1);
int estaoTodosMarcados(doHeap *vet, int n);
void desmarca(doHeap *vet, int n);
int intercalaSub(int TAMDADOS, char* filename, int* n_leituras, int* n_escrita, int* n_comparacoes);

#endif //INTERCALASUB