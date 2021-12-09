#include "ibqs.h"

int n_leituras_ibqs = 0;
int n_escritas_ibqs = 0;
int n_comparacoes_ibqs = 0;

int ibqs(int quantidade, char* filename, int* n_leituras, int* n_escrita, int* n_comparacoes, int p_flag){

    Aluno bloco[NBLOCOS];
    FILE* arq;

    if((arq = fopen(filename,"r")) == NULL){
        printf("Erro na abertura do arquivo\n");
        return 0;
    }

    FILE* fitas[F*2];
    //criando arquivos de fitas
    criar_fitas(F,fitas);
    char aux[1];
    int fita_index = 0;

    for(int i=0;i<quantidade/NBLOCOS;i++){
        n_comparacoes_ibqs++;
        //lendo um bloco completo
        for(int j=0;j<NBLOCOS;j++){
            n_comparacoes_ibqs++;
            fscanf(arq, "%ld %f %s", &bloco[j].inscricao,&bloco[j].nota,bloco[j].estado);
            //ignorando o proximo espaco
            fread(aux, 1, 1, arq);
            fread(bloco[j].cidade, 50, 1, arq);
            bloco[j].cidade[50] = '\0';
            //ignorando o proximo espaco
            fread(aux, 1, 1, arq);
            fread(bloco[j].curso, 30, 1, arq);
            bloco[j].curso[30] = '\0';
            n_leituras_ibqs+=5;
            if(p_flag)
                printf("%08ld %05.1f %s %s %s\n", bloco[j].inscricao, bloco[j].nota, bloco[j].estado, bloco[j].cidade, bloco[j].curso);
        }

        //ordenando bloco com quicksort na memoria principal
        quickSortInterno(bloco, 0, NBLOCOS-1);
        fita_index %= F;

        //escrevendo bloco em uma das fitas
        fwrite(&bloco, sizeof(Aluno), 20, fitas[fita_index]);

        //controlando qual ficha vai receber o bloco
        fita_index++;
    }

    //Pegando o ultimo bloco caso ele esteja incompleto
    int resto = quantidade%NBLOCOS;
    n_comparacoes_ibqs++;
    if(resto != 0){
        Aluno *memory = NULL;
        memory = (Aluno*) malloc(resto * sizeof(Aluno));
        n_comparacoes_ibqs++;
        if(memory == NULL){
            exit(EXIT_FAILURE);
        }
        for(int j=0;j<resto;j++){
            n_comparacoes_ibqs++;
            fscanf(arq, "%ld %f %s", &memory[j].inscricao,&memory[j].nota, memory[j].estado);
            fread(aux, 1, 1, arq);
            fread(memory[j].cidade, 50, 1, arq);
            memory[j].cidade[50] = '\0';
            fread(aux, 1, 1, arq);
            fread(memory[j].curso, 30, 1, arq);
            memory[j].curso[30] = '\0';
            memory[j].flag = 0;
            n_leituras_ibqs+=5;
            if(p_flag)
                printf("%08ld %05.1f %s %s %s\n", memory[j].inscricao, memory[j].nota, memory[j].estado, memory[j].cidade, memory[j].curso);
        }
        quickSortInterno(memory, 0, resto-1);
        fwrite(memory, resto * sizeof(Aluno), 1, fitas[fita_index]);
        free(memory);
    }

    //intercalacao
    if(p_flag)
        printf("\n\n");
    intercalacao(quantidade, fitas, bloco, n_leituras, n_escrita, n_comparacoes, p_flag);
    fclose(arq);
    for(int i = 0; i < 2*F; i++){
        fclose(fitas[i]);
    }
    *n_escrita += n_escritas_ibqs;
    *n_leituras += n_leituras_ibqs;
    *n_comparacoes += n_comparacoes_ibqs;
    return 1;
}