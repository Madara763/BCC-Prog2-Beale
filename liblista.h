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
    listano_t** ln;    //armazena um ponteiro para a lista das chaves correspondetes
    int tam;    //armazena a quantidade de caracteres que existem na lista
}lista_t;

lista_t* cria_lista();

int adiciona_lista(lista_t* lista, char c, int num);

void deleta_lista(lista_t* lista);

#endif