/*  Biblioteca Implementa as funções
    de Inserção e Busca da BST RedBlack
    Autor: Davi Garcia Lazzarin
    Data: 28/03/23
*/
#ifndef _LIB_RB_
#define _LIB_RB_

//Enum da cor do nó
typedef enum { VERMELHO, PRETO} Cor;

//Estrutura da arvore
typedef struct rb{
    struct rbno* raiz;
}rb_t;

//Estrutura do nó
typedef struct rbno{
    int chave;                       //numero da palavra
    Cor cor;                         //r ou b
    char letra;                      //primeira letra da palavra
    struct rbno* p;                  //ponteiros
    struct rbno* esq;                //ponteiros
    struct rbno* dir;                //ponteiros
}rbno_t;

//Cria a arvore
rb_t* criarb();

//Deleta todos os dados da arvore e desaloca a memória
void deleta_rb(rb_t* rb);

//Aloca o nó em memória e retorna o ponteiro para ele
rbno_t* criano(int chave, char letra);

//Cria um nó com os valores passados e inclui na arvore
int inclui_rb(rb_t* arv, int chave, char letra);

//Faz a leitura em ordem da arvore
void leitura_rb(rb_t* no);

//busca a o nó da chave passada como parametro
//se achar retorna um ponteiro para uma cópia da letra que havia no nó
char busca_rb(rb_t* arv, int chave);
#endif