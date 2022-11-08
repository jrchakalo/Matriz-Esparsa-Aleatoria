//Autor: José Izaias da Silva Júnior
//Data: 08/11/2022
//Nome do projeto: Matriz Esparsa Aleatoria

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//Defines gerais.
#define LIN 3
#define COL 3
#define RMAX 20
//para ter menos elementos preenchidos na matriz e realmente ser uma matriz esparsa.
#define NUMPOS COL-2

//estrutura para representar a tupla (posicao, valor).
struct tupEsp{
    float val;
    int posi;
};

//escopo de funcoes.
void preencheEsparsa(struct tupEsp esparsa[LIN][COL]);
void printEsparsa(struct tupEsp esparsa[LIN][COL]);

int main (void){
    struct tupEsp esparsa[LIN][COL];

    //funcao para randomizar os valores a cada execucao do programa.
    srand(time(NULL));

    //cria uma matriz esparsa e printa ela.
    preencheEsparsa(esparsa);
    printEsparsa(esparsa);
}

//funcao para preencher uma matriz esparsa.
void preencheEsparsa(struct tupEsp esparsa[LIN][COL]){
    //define um valor aleatorio entre 1 e NUMPOS para quantos valores da linha serao preenchidos.
    int numpos = 1 + rand() % (NUMPOS);
    int pos=0;
    int aux=999;
    int cont=0;
    int verif=0;

    for (int i=0; i < LIN; i++){
        //for para preencher na linha apenas a quantidade de colunas sorteadas.
        for (int j=0; j < numpos;j++){
            //sorteia a coluna que vai ser preenchida.
            pos = rand() % COL;
            //while infinito para evitar sobrescrita.
            while(1){
                //variavel auxiliar inicia com numero alto para garantir entrada no if.
                if(aux != pos){
                    //coloca a posicao sorteada na matriz esparsa.
                    esparsa[i][pos].posi = pos;
                    //preenche o valor da posicao sorteada com um numero aleatorio de um certo intervalo.
                    esparsa[i][pos].val = -9.0 + (((float) rand()) / ((float) RAND_MAX) * RMAX);
                    //while infinito para tratar erros.
                    while(1){    
                        //se o valor da coluna 0 em qualquer linha for muito baixo eh lixo.
                        if(esparsa[i][0].val < 0.001){
                            //entao coloca uma um valor alto na posicao para ele ser identificado como lixo.
                            esparsa[i][0].posi = 100 + rand();
                        }
                        //se o valor sorteado for muito pequeno foge da zona do printf.
                        if (esparsa[i][pos].val < 0.001){
                            //entao sorteia outro numero.
                            esparsa[i][pos].val = -9.0 + (((float) rand()) / ((float) RAND_MAX) * RMAX);
                            //e soma um na variavel verificadora.
                            verif++;
                        }else{
                            //que serve somente para garantir que possa haver numeros negativos na matriz.
                            if(verif != 0){
                                esparsa[i][pos].val = -esparsa[i][pos].val;
                                verif = 0;
                            }
                            //sai do loop infinito da correcao.
                            break;
                        }
                    }
                    //salva a ultima posicao.
                    aux = pos;
                    //sai do loop infinito que evita sobrescricao.
                    break;
                }else{
                    //se cair uma posicao igual a anterior, sorteia outra.
                    pos = rand() % COL;
                }
            }        
        }
        //sorteia outra quantidade de colunas que seram preenchidas na proxima linha.
        numpos = 1 + rand() % (NUMPOS);
    }
}

void printEsparsa(struct tupEsp esparsa[LIN][COL]){
    //for para printar a matriz produzida.
    for (int i=0; i < LIN;i++){
        for (int j=0; j<COL; j++){
            
            //verificacao para evitar os espacos que sao lixo.
            if (esparsa[i][j].posi <= COL && esparsa[i][j].posi == j){
                printf("(%d, %.2f) ", esparsa[i][j].posi, esparsa[i][j].val);
            }else{
                //print estetico para nao imprimir o lixo ou deixar em branco.
                printf("(%d, %.2f) ", j, 0.0);
            }
        }
        puts("");
    }    
}