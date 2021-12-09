#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "qSortExt.h"
#include <stdlib.h>
#include <string.h>
#define TAMANHOAREA 20 // Tamanho do pivô do quicksort

int n_leituras_qsext = 0;
int n_escritas_qsext = 0;
int n_comparacoes_qsext = 0;

void QuicksortExterno(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir)
{
    int i, j;
    n_comparacoes_qsext++;
    if (Dir - Esq < 1)
        return;
    TipoArea area;
    area.Area = malloc(TAMANHOAREA * sizeof(TipoDado));
    area.tam = 0;
    Particao(ArqLi, ArqEi, ArqLEs, area, Esq, Dir, &i, &j);
    n_comparacoes_qsext++;
    if (i - Esq < Dir - j)
    {
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i);
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir);
    }
    else
    {
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir);
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i);
    }
    free(area.Area);
}

void leSup(FILE **ArqLes, TipoDado *UltLido, int *Ls, short *OndeLer)
{
    fseek(*ArqLes, (*Ls - 1) * sizeof(TipoDado), SEEK_SET);
    fread(UltLido, sizeof(TipoDado), 1, *ArqLes);
    n_leituras_qsext++;

    (*Ls)--;
    *OndeLer = 0;
}

void leInf(FILE **ArqLi, TipoDado *UltLido, int *Li, short *OndeLer)
{
    fread(UltLido, sizeof(TipoDado), 1, *ArqLi);
    n_leituras_qsext++;

    (*Li)++;
    *OndeLer = 1;
}

void InserirArea(TipoArea *Area, TipoDado *UltLido, int *NRArea)
{
    insereItem(*UltLido, Area);
    *NRArea = Area->tam;
}

void insereItem(TipoDado valor, TipoArea *Area)
{
    int c;

    for (c = Area->tam - 1; ((c >= 0) && (Area->Area[c].nota > valor.nota)); c--) // Vai "empurrando" os valores para trás até chegar na posição que deve ficar
    {
        Area->Area[c + 1] = Area->Area[c];
    }
    Area->Area[c + 1] = valor; // Coloca valor na posição livre que empurrou e atualiza tamanho
    Area->tam++;
}

void EscreveMax(FILE **ArqLEs, TipoDado R, int *Es)
{
    fseek(*ArqLEs, (*Es - 1) * sizeof(TipoDado), SEEK_SET);
    n_escritas_qsext++;
    fwrite(&R, sizeof(TipoDado), 1, *ArqLEs);

    (*Es)--;
}

void EscreveMin(FILE **ArqEi, TipoDado R, int *Ei)
{
    n_escritas_qsext++;
    fwrite(&R, sizeof(TipoDado), 1, *ArqEi);
    (*Ei)++;
}

void RetiraMax(TipoArea *area, TipoDado *R, int *NRArea)
{
    *R = area->Area[area->tam - 1]; // Remove último elemento, colocando em *R, e então diminui quantos espaços da área estão ocupados
    area->tam--;
    *NRArea = area->tam;
}

void RetiraMin(TipoArea *area, TipoDado *R, int *NRArea)
{
    int c;
    *R = area->Area[0]; // Retira primeiro elemento, puxando os subsequentes uma posição à frente
    area->tam--;
    for (c = 0; c < area->tam; c++)
    {
        area->Area[c] = area->Area[c + 1];
    }

    *NRArea = area->tam;
}

void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, TipoArea area, int esq, int dir, int *i, int *j) // Processo de particionamento com pivô
{
    int Ls = dir;
    int Es = dir;
    int Li = esq;
    int Ei = esq;
    int NRArea = 0;
    int Linf = INT_MIN;
    int Lsup = INT_MAX;

    short OndeLer = 1;
    TipoDado UltLido, R;

    fseek(*ArqLi, (Li - 1) * sizeof(TipoDado), SEEK_SET);
    fseek(*ArqEi, (Ei - 1) * sizeof(TipoDado), SEEK_SET);

    *i = esq - 1;
    *j = dir + 1;

    while (Ls >= Li)
    {
        n_comparacoes_qsext++;
        if (NRArea < TAMANHOAREA - 1)
        {
            n_comparacoes_qsext++;
            if (OndeLer)
                leSup(ArqLEs, &UltLido, &Ls, &OndeLer);
            else
                leInf(ArqLi, &UltLido, &Li, &OndeLer);
            InserirArea(&area, &UltLido, &NRArea);
            continue;
        }

        n_comparacoes_qsext++;
        if (Ls == Es)
            leSup(ArqLEs, &UltLido, &Ls, &OndeLer);
        else {
            n_comparacoes_qsext++;
            if (Li == Ei)
                leInf(ArqLi, &UltLido, &Li, &OndeLer);
            else{ 
                n_comparacoes_qsext++;
                if (OndeLer)
                    leSup(ArqLEs, &UltLido, &Ls, &OndeLer);
                else
                    leInf(ArqLi, &UltLido, &Li, &OndeLer);
            }
        }

        n_comparacoes_qsext++;
        if (UltLido.nota > Lsup) // Comparações com limites
        {
            *j = Es;
            EscreveMax(ArqLEs, UltLido, &Es);
            continue;
        }

        n_comparacoes_qsext++;
        if (UltLido.nota < Linf)
        {
            *i = Ei;
            EscreveMin(ArqEi, UltLido, &Ei);
            continue;
        }

        InserirArea(&area, &UltLido, &NRArea);
        n_comparacoes_qsext++;
        if (Ei - esq < dir - Es)
        {
            RetiraMin(&area, &R, &NRArea);
            EscreveMin(ArqEi, R, &Ei);
            Linf = R.nota;
        }
        else
        {
            RetiraMax(&area, &R, &NRArea);
            EscreveMax(ArqLEs, R, &Es);
            Lsup = R.nota;
        }
    }

    while (Ei <= Es)
    {
        n_comparacoes_qsext++;
        RetiraMin(&area, &R, &NRArea);
        EscreveMin(ArqEi, R, &Ei);
    }
}

void learq(char *qualArquivo, int N_elementos, int p_flag) // Faz a leitura do arquivo .txt original e transforma em um arquivo binário que será usado no quicksort
{
    TipoDado aux;
    char lixo[1]; //Variável para tomar conta de espaços em branco
    FILE *arquivoTexto;
    FILE *arquivoBin;
    arquivoTexto = fopen(qualArquivo, "r");
    arquivoBin = fopen("convBin.dat", "w+b");
    for (int c = 0; c < N_elementos; c++)
    {
        fscanf(arquivoTexto, "%ld %lf %s", &aux.numInsc, &aux.nota, aux.estado);
        
        fread(lixo, 1, 1, arquivoTexto);
        fread(aux.cidade, 50, 1, arquivoTexto);
        aux.cidade[50] = '\0';
        // ignorando o proximo espaco
        fread(lixo, 1, 1, arquivoTexto);
        fread(aux.curso, 30, 1, arquivoTexto);
        aux.curso[30] = '\0';

        if(p_flag)
            printf("%08ld %05.1f %s %s %s\n", aux.numInsc, aux.nota, aux.estado, aux.cidade, aux.curso);
        fwrite(&aux, sizeof(TipoDado), 1, arquivoBin);
    }
    if(p_flag) printf("\n\n");
    fclose(arquivoTexto);
    fclose(arquivoBin);
}

int QuickSortExternoPrograma(int N_elementos, char *qualArquivo, int *numLeituras, int *numEscritas, int *numComparacoes, int p_flag) // Programa principal
{
    learq(qualArquivo, N_elementos, p_flag);

    FILE *ArqLi, *ArqEi, *ArqLES;
    if ((ArqLi = fopen("convBin.dat", "r+b")) == NULL) //Inicialização dos arquivos e passagem de seus ponteiros para o algoritmo
    {
        printf("Erro na abertura do arquivo\n");
        return 0;
    }

    if ((ArqEi = fopen("convBin.dat", "r+b")) == NULL)
    {
        printf("Erro na abertura do arquivo\n");
        return 0;
    }

    if ((ArqLES = fopen("convBin.dat", "r+b")) == NULL)
    {
        printf("Erro na abertura do arquivo\n");
        return 0;
    }

    QuicksortExterno(&ArqLi, &ArqEi, &ArqLES, 1, N_elementos);

    fclose(ArqEi);
    fclose(ArqLES);
    fclose(ArqLi);

    escrevearq("convBin.dat", N_elementos, p_flag);

    *numLeituras = n_leituras_qsext;
    *numEscritas = n_escritas_qsext;
    *numComparacoes = n_comparacoes_qsext;
    return 1;
}

void escrevearq(char *qualArquivo, int N_elementos, int p_flag) // Função que transforma o arquivo binário já ordenado de volta em um txt para saída
{
    TipoDado aux;
    FILE *arquivoTexto;
    FILE *arquivoBin;
    arquivoBin = fopen(qualArquivo, "rb");
    arquivoTexto = fopen("saida.txt", "w+");
    for (int c = 0; c < N_elementos; c++)
    {
        fread(&aux, sizeof(TipoDado), 1, arquivoBin);
        fprintf(arquivoTexto, "%ld %lf %s %s %s\n", aux.numInsc, aux.nota, aux.estado, aux.cidade, aux.curso);
        if(p_flag)
            printf("%08ld %05.1f %s %s %s\n", aux.numInsc, aux.nota, aux.estado, aux.cidade, aux.curso);
    }
    fclose(arquivoTexto);
    fclose(arquivoBin);
}
