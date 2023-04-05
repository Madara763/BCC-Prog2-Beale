#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef _LIB_L_
#define _LIB_L_
#define STDTAM 100

typedef struct listano{
    int* chaves;
    int tam;
}listano_t;

typedef struct lista{
    char* l;    //armazena os caracteres que existem no arquivo de chave
    listano_t* ln;    //armazena um ponteiro para a lista das chaves correspondetes
    int tam;    //armazena a quantidade de caracteres que existem na lista
}lista_t;

lista_t* crialista(){
    //a lista em si
    lista_t* lista=malloc(sizeof(lista_t));
    if(!lista)
        return NULL;

    //vetor dos char
    lista->l=malloc(sizeof(char));
    if(!lista->l)
        return NULL;
    
    //vetor de ponteiros para os nós, onde tem os numeros
    lista->ln=malloc(sizeof(listano_t));
    if(!lista->ln)
        return NULL;
    
    lista->tam=0;
    return lista;
}//crialista

int adicionalista(lista_t* lista, char c, int num){
    // VERIFICANDO SE O CHAR JA EXISTE ANTES DE ADICIONAR O NUMERO DELE NA ESTRUTURA
    for(int i=0;i<lista->tam;i++){
        if(lista->l[i]==c){
            
            //salav um ptr para o vetor
            int *aux=lista->ln[i]->no->chaves;  
            //aloca um vetor com um espaço a mais e o atribui na estrutura
            lista->ln[i]->no->chaves=malloc(sizeof(int)*lista->ln[i]->no->tam+1);  
            for(!lista->ln[i]->no->chaves){
                perror("Erro de alocação");
                return 0;
            }

            //copia os valores para o novo vetor com um tamanho a mais
            for(int auxn=0;auxn<tam;auxn++){    
                lista->ln[i]->no->chaves[auxn]=aux[auxn];    
            }
            //salva o ultimo numero da ocorrencia na estrutura
            lista->ln[i]->no->chaves[auxn]=num; 

            //aumenta o tamanaho do nó
            lista->ln[i]->no->tam++;
            
            //libera memória do antigo vetor
            free(aux);
            return 1;
        }
    }

    //adiciona o novo char a estrutura
    char* auxstr=lista->l;
    lista->l=malloc(sizeof(char)*lista->tam);
    if(!lista->l)
        return 0;

    strcpy(lista->l, auxstr);
    lista->l[lista->tam]=c;
    free(auxstr);

    listano_
      
    //adiciona o numero correspondente a estrutura
    listano_t* no=malloc(sizeof(int));
    if(!no)
        return 0;
    
    lista

    //
    lista->tam++;
    return 1;
}


#endif