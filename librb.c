/*  Biblioteca Implementa as funções
    de Inserção e Busca da BST RedBlack
    Autor: Davi Garcia Lazzarin
    Data: 28/03/23
*/
#include<stdio.h>
#include<stdlib.h>
#include"librb.h"

rb_t* criarb(){
    rb_t* arv;
    arv=malloc(sizeof(rb_t));
    if (!arv){
        perror("Erro de alocação.\n");
        return NULL;
    };
    return arv;    
}//criarb

rbno_t* criano(int chave, char letra){
    
    rbno_t *no;
    no=malloc(sizeof(rbno_t));
    if (!no){
        perror("Erro de alocação.\n");
        return NULL;
    };

    no->chave=chave;
    no->letra=letra;
    no->cor='v';

    no->p=NULL;
    no->esq=NULL;
    no->dir=NULL;

    return no;
}//cria no
