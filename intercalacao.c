#include "intercalacao.h"

void intercalacao(int qte, FILE **fitas, Aluno *mem){
    Memoria memoria; //Memoria Interna da Maquina
    int vez = 1; //A "vez" da intercalacao. Inicializada com 1 pq eh a 1a intercalacao
    int FimExec = 0; //Bool que indica FimExecucao = falso
    int QteFitas; // Qte de fitas necessarias para ordenar os registros
    long pow; //potencia
    while(!FimExec){
        pow = int_pow(F, vez);
        QteFitas = qte / pow;
        int u = F * ((vez+1) % 2); //Variavel que, ora eh 0, ora eh 20, para colocar na fita certa
        //Comparacao++
        if((qte % pow) != 0){
            QteFitas++;
        }
        //comparacao++
        if(QteFitas <= F){
            FimExec = 1; //Caso a qte de fitas para ordenar os registros seja menor que a qte de registro, essa sera a ultima intercalaçao
            for(int i = 0; i < QteFitas; i++){
                fseek(fitas[i + u], 0, SEEK_SET);
            }
        }
        else{
            for(int i = 0; i < F; i++){
                fseek(fitas[i+u], 0, SEEK_SET);
            }
        }
        for(int i = 0; i < 20; i++){
            //tranferencia++
            fread(&memoria.bloco[i], sizeof(Aluno), 1, fitas[(i % QteFitas) + u]);
            memoria.fonteFita[i] = (i % QteFitas) + u;
        }
        memoria = shellsort(memoria, 20);
        int lidos = 20; // Variavel que indica qtos registros foram lidos ate o momento
        int j;
        j = 0;
        //comparacao++
        while(lidos < qte){
            //comparacao++
            colocarnaFita(memoria.bloco[0], fitas[(j % F) + (F * (vez % 2))]);
            if(fitaIndisponivel(fitas[memoria.fonteFita[0]])){
                int m; //variavel auxiliar que indica onde esta o menor registro das fitas
                //comparacao++
                if(QteFitas <= F)
                    m = pegaMenorFita(fitas, QteFitas, u);
                else
                    m = pegaMenorFita(fitas, F, u);
                int FimBlocos = 0; //Booleano que indica se acabou os registros de todos os blocos
                if(m == -1){
                    FimBlocos = 1;
                }
                if(FimBlocos){ //Caso seja o Fim de todos os blocos
                    for(int i = 1; i < 20; i++){
                        //transferecia++
                        fwrite(&memoria.bloco[i], sizeof(Aluno), 1, fitas[(j % F) + (F * (vez % 2))]); //Colocar os registros que estao na memoria na fita
                    }
                    j++;
                    if(QteFitas > F){
                        QteFitas -= 20; //Ja foram utilizadas todas as fitas disponiveis, entao hora de reaproveitar
                        for(int i = 0; i < 20; i++){
                            //tranferencia++
                            fread(&memoria.bloco[i], sizeof(Aluno), 1, fitas[(i % QteFitas) + u]);
                            lidos++;
                            memoria.fonteFita[i] = (i % QteFitas) + u;
                        }
                        memoria = shellsort(memoria, 20); //Ordena a memoria
                        continue; //Reinicia o loop
                    }
                }
                else{ //Pegar o menor registro dentre todas as fitas
                    //transferencia++
                    fread(&memoria.bloco[0], sizeof(Aluno), 1, fitas[m]);
                    lidos++;
                    memoria.fonteFita[0] = m;
                }
            }
            else{
                //tranferencia++
                fread(&memoria.bloco[0], sizeof(Aluno), 1, fitas[memoria.fonteFita[0]]);
                lidos++;
            }
            memoria = shellsort(memoria, 20); //Ordena a memoria
        }//Aqui, todos os registros foram lidos, mas nem todos foram colocados. Faltam os ultimos 20 registros que estao na memoria
        //transferencia dos ultimos 20 registros
        //tranferencia++
        fwrite(memoria.bloco, 20 * sizeof(Aluno), 1, fitas[(j % F) + (F * (vez % 2))]);
        for(int i = 0; i < 20; i++)
            fseek(fitas[i + (F * ((vez+1) % 2))], 0, SEEK_SET);
        vez++;//Indica a + 1 intercalacao
    }
    vez--; //Decremento da variavel para achar a fita de destino certa

    //A INTERCALACAO ACABA AQUI, A FUNCAO ABAIXO NAO FAZ PARTE DA INTERCALACAO

    bintoTxt(qte, fitas[F * (vez % 2)], "saida.txt"); //Transformar binario em texto
}

void bintoTxt(int qte, FILE *fita, char *nome){
    fseek(fita, 0, SEEK_SET);
    FILE *saida = fopen(nome, "w");
    Aluno aux;
    while(fread(&aux, sizeof(Aluno), 1, fita)){
        fprintf(saida, "%08ld %05.1f %s %s %s\n", aux.inscricao, aux.nota, aux.estado, aux.cidade, aux.curso);
    }
    fclose(saida);
}

int fitaIndisponivel(FILE *fita){
    Aluno aux[2];
    fseek(fita, -sizeof(Aluno), SEEK_CUR);
    //tranferencia++
    if(fread(aux, sizeof(Aluno), 2, fita) < 2){//Se retornar diferente de 2, quer dizer o fim da fita
        return 1;
    }
    fseek(fita, -sizeof(Aluno), SEEK_CUR); //Reposiciona o ponteiro do arquivo no lugar certo
    //comparacao++
    return (aux[1].nota < aux[0].nota);
}

void colocarnaFita(Aluno x, FILE *fita){
    //transferencia++
    fwrite(&x, sizeof(Aluno), 1, fita);
}

Memoria shellsort(Memoria v, int n){
    int h = 1;
    //comparacao++
    while(h < n)//comparacao++
        h = 3 * h + 1;
    do{
        h = (h-1) / 3;
        for(int i = h; i < n; i++){
            Aluno aux1 = v.bloco[i];
            int aux2 = v.fonteFita[i];
            int j = i;
            //comparacao++
            while(v.bloco[j-h].nota > aux1.nota){//comparacao++
                v.bloco[j] = v.bloco[j-h];
                v.fonteFita[j] = v.fonteFita[j-h];
                j = j-h;
                if(j < h)//comparacao++
                    break;
            }
            v.bloco[j] = aux1;
            v.fonteFita[j] = aux2;
        }
    } while (h != 1);//comparacao++
    return v;
    
}
int int_pow(int base, int exp){
    int r = 1;
    for(int i = 0; i < exp; i++)
        r *= base;
    return r;
}

int pegaMenorFita(FILE **fitas, int QteFitas, int u){
    int menorFita = -1; //Variavel que retorna em qual fita esta o menor registro. -1 indica que nao foi encontrado nenhum registro
    int i = 0;
    Aluno menorValor;
    Aluno aux;
    //comparacao++
    while(i < QteFitas){
        //comparacao++
        if(fitaIndisponivel(fitas[i+u])){
            i++;
        }
        else{
            break;
        }
    }
    //comparacao++
    for(i; i < QteFitas; i++){
        //comparacao++
        //comparacao++
        if(menorFita == -1){
            //transferencia++
            fread(&menorValor, sizeof(Aluno), 1, fitas[i+u]);
            fseek(fitas[i+u], -sizeof(Aluno), SEEK_CUR);
            menorFita = i+u;
        }
        else{
            if(!fitaIndisponivel(fitas[i+u])){
                //tranferencia++
                fread(&aux, sizeof(Aluno), 1, fitas[i+u]);
                fseek(fitas[i+u], -sizeof(Aluno), SEEK_CUR);
                //comparacao++
                if(aux.nota < menorValor.nota){
                    menorValor = aux;
                    menorFita = i+u;
                }
            }
        }

    }
    return menorFita;
}