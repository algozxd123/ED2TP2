#ifndef IBQS_H
#define IBQS_H

#include <stdio.h>
#include "aluno.h"
#include "qsin.h"
#include "fitas.h"
#include "intercalacao.h"

#define NBLOCOS 20

int ibqs(int quantidade, char* filename, int* n_leituras, int* n_escrita, int* n_comparacoes, int p_flag);
#endif