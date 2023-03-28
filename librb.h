/*  Biblioteca Implementa as funções
    de Inserção e Busca da BST RedBlack
    Autor: Davi Garcia Lazzarin
    Data: 28/03/23
*/

typedef struct rbno_t{
    int chave;
    char cor;
    char letra;
    rbno_t *p, *esq, *dir;
}rbno_t;

typedef struct rb_t{
    rbno_t* raiz;
}rb_t;

rb_t* criarb();

rbno_t* criano(int chave, char letra);
