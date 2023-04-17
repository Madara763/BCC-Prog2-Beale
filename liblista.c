/*
    Essa biblioteca implementa uma lista de caracteres linkada a uma lista de chaves, feita especificamente para o trabalho beale
    Feito por Davi Lazzarin
    Data: 12/04/2023 
*/
#include"liblista.h"

lista_t* cria_lista(){
    //a lista em si
    lista_t* lista=malloc(sizeof(lista_t));
    if(!lista)
        return NULL;
    
    lista->l=NULL;
    lista->ln=NULL;
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
    }
        free(lista->l);
        lista->l=NULL;

        free(lista->ln);
        lista->ln=NULL;

        lista->tam=0;

        free(lista);
        lista=NULL; 
    
}//deletalista

int adiciona_lista(lista_t* lista, char c, int num){

    // VERIFICANDO SE O CHAR JA EXISTE ANTES DE ADICIONAR O NUMERO DELE NA ESTRUTURA
    int i=0;
    for(i=0;i<lista->tam;i++){
        if(lista->l[i]==c){
            
            //aumenta o tamanho do vetor de chaves
            lista->ln[i]->chaves = (int*) realloc(lista->ln[i]->chaves, (sizeof(int) * (lista->ln[i]->tam + 1)) ); 
            
            //testa o novo tamanho
            if(lista->ln[i]->chaves == NULL){
                perror("Erro de alocação\n");
                return 0;
            }

            //adiciona o novo valor no final do vetor
            lista->ln[i]->chaves[lista->ln[i]->tam]=num;
            lista->ln[i]->tam++;

            return 1;
        }
    }

    //CRIANDO UMA NOVA LISTA DE CHAVES PARA UM NOVO CARACTERE
    lista->tam++;

    //aumenta o tamanho do vetor de caracteres
    lista->l = (char*) realloc(lista->l, (sizeof(char)*lista->tam) + 1); 
    
    //testa o novo tamanho
    if(lista->l == NULL){
        perror("Erro de alocação\n");
        return 0;
    }

    //adiciona o char no vetor de caracteres
    lista->l[lista->tam-1]=c;

    //aumenta o tamanho do vetor ponteiros para as chaves
    lista->ln = (listano_t**) realloc(lista->ln, (sizeof(listano_t**) * (lista->tam + 1)) ); 

    //testa o novo tamanho
    if(lista->ln == NULL){
        perror("Erro de alocação\n");
        return 0;
    }

    //Cria o novo nó
    listano_t* auxno=malloc(sizeof(listano_t));

    //cria o novo vetor de chaves
    int *aux=malloc(sizeof(int)); 

    //testa o novo vetor
    if(aux==NULL){
        perror("Erro de alocação\n");
        return 0;
    }

    //adiciona o novo valor no final do vetor
    auxno->chaves=aux;
    auxno->chaves[0]=num;
    auxno->tam=1;
    lista->ln[lista->tam-1]=auxno; 

    return 1;
}//adiciona_lista

//retorna um int para ser usado como codigo de um char recebido caso o char exista na lista
//retorna -1 caso não encontre o char
int busca_cod_lista(lista_t* lista, char c){

    int i=0, n;
    
    for(i=0;i<lista->tam;i++){
        if(lista->l[i]==c){

            n=rand() % (lista->ln[i]->tam); 
            return lista->ln[i]->chaves[n];
        }
    }

    return -1;
}//busca_cod_lista

//Imprime a lista em um arquivo, vinculando cada letra aos seus numeros
void imprime_lista(lista_t* lista, FILE* arqchaves){

    for(int i=0; i<lista->tam; i++){
        fprintf(arqchaves, "%c:", lista->l[i]);
        for (int j=0; j < lista->ln[i]->tam; j++){
            fprintf(arqchaves, " %d", lista->ln[i]->chaves[j]);
        }
        fprintf(arqchaves, "\n");    
    }

}//imprime_lista