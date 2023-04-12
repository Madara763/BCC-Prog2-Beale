/*
    Essa biblioteca implementa uma lista de caracteres linkada a uma lista de chaves
    Feito por Davi Lazzarin
    Data: 12/04/2023 
*/
#include"liblista.h"

lista_t* cria_lista(){
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

//apaga os dados e libera memória da lista
void deleta_lista(lista_t* lista){
    if(lista != NULL){
        int i,j=0;
        for(i=0; i<lista->tam; i++){
            j=lista->ln[i]->tam-1;
            while (j>=0){
                lista->ln[i]->chaves[j]=0;
                j--;
            }
            
            free(lista->ln[i]->chaves);
            lista->ln[i]->chaves=NULL;
            lista->ln[i]->tam=0;

            free(lista->ln[i]);
            lista->ln[i]=NULL;

            lista->l[i]='\0';
        }

        free(lista->l);
        lista->l=NULL;

        free(lista->ln);
        lista->ln=NULL;

        lista->tam=0;

        free(lista);
        lista=NULL;
    }
}//deletalista

int adiciona_lista(lista_t* lista, char c, int num){

    // VERIFICANDO SE O CHAR JA EXISTE ANTES DE ADICIONAR O NUMERO DELE NA ESTRUTURA
    int i;
    for(i=0;i<lista->tam;i++){
        if(lista->l[i]==c){
            
            //aumenta o tamanho do vetor de chaves
            long int tamanho=(sizeof(lista->ln[i]->chaves))/(sizeof(int));

            int *aux=realloc(lista->ln[i]->chaves, (sizeof(int)*lista->ln[i]->tam) + 1); 
            
            long int novotamanho=(sizeof(aux))/(sizeof(int));

            //testa o novo tamanho
            if(tamanho == novotamanho){
                perror("Erro de alocação\n");
                return 0;
            }

            //adiciona o novo valor no final do vetor
            lista->ln[i]->chaves=aux;
            lista->ln[i]->tam++;
            lista->ln[i]->chaves[lista->ln[i]->tam]=num;

            return 1;
        }
    }

    //CRIANDO UMA NOVA LISTA DE CHAVES PARA UM NOVO CARACTERE

    //aumenta o tamanho do vetor de caracteres
    long int tamanho=(sizeof(lista->l))/(sizeof(char));

    char *auxc=realloc(lista->l, (sizeof(char)*lista->tam) + 1); 
            
    long int novotamanho=(sizeof(auxc))/(sizeof(char));

    //testa o novo tamanho
    if(tamanho == novotamanho){
        perror("Erro de alocação\n");
        return 0;
    }

    //adiciona o char no vetor de caracteres
    lista->l=auxc;
    lista->l[i]=c;


    //aumenta o tamanho do vetor ponteiros para as chaves
    tamanho=(sizeof(lista->ln))/(sizeof(listano_t*));

    listano_t *auxl=realloc(lista->ln, (sizeof(listano_t*)*lista->tam) + 1); 
            
    novotamanho=(sizeof(auxl))/(sizeof(listano_t*));

    //testa o novo tamanho
    if(tamanho == novotamanho){
        perror("Erro de alocação\n");
        return 0;
    }

    lista->ln=auxl;
    lista->tam++;


    //cria o novo vetor de chaves
    int *aux=malloc(sizeof(int)); 

    //testa o novo vetor
    if(aux==NULL){
        perror("Erro de alocação\n");
        return 0;
    }

    //adiciona o novo valor no final do vetor
    lista->ln[i]->chaves=aux;
    lista->ln[i]->tam++;
    lista->ln[i]->chaves[lista->ln[i]->tam]=num;

    return 1;
}