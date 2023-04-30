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

//alloca memória para a lista
lista_t* cria_lista();

//adiciona um char e a sua chave na lista
int adiciona_lista(lista_t* lista, char c, int num);

//apaga a lista e limpa a meória
void deleta_lista(lista_t* lista);

//busca o char na lista e devolve um int aleatório dentre os correspondentes aquele char
int busca_cod_lista(lista_t* lista, char c);

//imprime a lista em um arquivo
void imprime_lista(lista_t* lista, FILE* arqchaves);

//Verifica a integridade da lista
void integra_lista(lista_t* lista, int i);

#endif