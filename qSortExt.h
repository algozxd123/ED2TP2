#include <stdio.h>
#ifndef QSEX_H
#define QSEX_H

typedef struct 
{
    long numInsc;
    double nota;
    char estado[3];
    char cidade[51];
    char curso[31];

} TipoDado;

typedef struct area
{
    TipoDado *Area;
    int tam;
} TipoArea;


void leSup(FILE **ArqLes, TipoDado *UltLido, int *Ls, short *OndeLer);
void leInf(FILE **ArqLi, TipoDado *UltLido, int *Li, short *OndeLer);
void learq(char *qualArquivo, int N_elementos);
void escrevearq(char *qualArquivo, int N_elementos);

void InserirArea (TipoArea *Area, TipoDado *UltLido, int *NRArea);
void insereItem(TipoDado valor, TipoArea *Area);
void RetiraMin(TipoArea *area, TipoDado *R, int *NRArea);
void RetiraMax(TipoArea *area, TipoDado *R, int *NRArea);
void EscreveMin(FILE **ArqEi, TipoDado R, int *Ei);

void Particao( FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, TipoArea area, int esq, int dir, int *i, int *j);
void QuicksortExterno(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir);
int QuickSortExternoPrograma(int N_elementos, char *qualArquivo, int *numLeituras, int *numEscritas, int *numComparacoes);

#endif
