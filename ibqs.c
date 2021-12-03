#include "ibqs.h"

int n_leituras_ibqs = 0;
int n_escritas_ibqs = 0;
int n_comparacoes_ibqs = 0;

int ibqs(int quantidade, char* filename, int* n_leituras, int* n_escrita, int* n_comparacoes){

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
        //lendo um bloco completo
        for(int j=0;j<NBLOCOS;j++){
            fscanf(arq, "%ld %f %s", &bloco[j].inscricao,&bloco[j].nota,bloco[j].estado);
            //ignorando o proximo espaco
            fread(aux, 1, 1, arq);
            fread(bloco[j].cidade, 50, 1, arq);
            bloco[j].cidade[50] = '\0';
            //ignorando o proximo espaco
            fread(aux, 1, 1, arq);
            fread(bloco[j].curso, 30, 1, arq);
            bloco[j].curso[30] = '\0';
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
    if(resto != 0){
        Aluno *memory = NULL;
        memory = (Aluno*) malloc(resto * sizeof(Aluno));
        if(memory == NULL){
            exit(EXIT_FAILURE);
        }
        for(int j=0;j<resto;j++){
            fscanf(arq, "%ld %f %s", &memory[j].inscricao,&memory[j].nota, memory[j].estado);
            fread(aux, 1, 1, arq);
            fread(memory[j].cidade, 50, 1, arq);
            memory[j].cidade[50] = '\0';
            fread(aux, 1, 1, arq);
            fread(memory[j].curso, 30, 1, arq);
            memory[j].curso[30] = '\0';
            memory[j].flag = 0;
        }
        quickSortInterno(memory, 0, resto-1);
        fwrite(memory, resto * sizeof(Aluno), 1, fitas[fita_index]);
        free(memory);
    }

    //intercalacao
    intercalacao(quantidade, fitas, bloco);
    return 0;
}