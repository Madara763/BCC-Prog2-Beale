/*
    Essa biblioteca implementa uma lista de caracteres linkada a uma lista de chaves, feita especificamente para o trabalho beale
    Feito por Davi Lazzarin
    Data: 12/04/2023 
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

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

int busca_cod_lista(lista_t* lista, char c);

void imprime_lista(lista_t* lista, FILE* arqchaves);

#endif