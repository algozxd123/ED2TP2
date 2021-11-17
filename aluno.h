#ifndef ALUNO_H
#define ALUNO_H

typedef struct{
    long inscricao;
    float nota;
    char estado[3];
    char cidade[51];
    char curso[31];
    int flag;
} Aluno;
#endif