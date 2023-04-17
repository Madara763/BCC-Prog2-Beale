/*  Biblioteca Implementa as funções
    de Inserção e Busca da BST VERMELHOPRETO
    Autor: Davi Garcia Lazzarin
    Data: 28/03/23
*/
#include<stdio.h> 
#include<stdlib.h>
#include"librb.h"

//Cria a arvore
rb_t* criarb(){
    rb_t* arv;
    arv=malloc(sizeof(rb_t));
    if (!arv){
        perror("Erro de alocação\n");
        return NULL;
    };
    arv->raiz=NULL;
    return arv;    
}//criarb

//Deleta um nó desaloca a memória
void deleta_no_rb(rbno_t* no){
    if (no->esq != NULL)
        deleta_no_rb(no->esq);
    
    if(no->dir != NULL)
        deleta_no_rb(no->dir);
    
    no->chave=0;
    no->cor=VERMELHO;
    no->letra='0';
    no->p=NULL;
    free(no);
}//deleta_no_rb

//Deleta todos os dados da arvore e desaloca a memória
void deleta_rb(rb_t* rb){
    if(rb->raiz != NULL)
        deleta_no_rb(rb->raiz);
    
    free(rb);
}//deleta_rb

//Função auxiliar da inclusão que cria o nó, retorna um ponteiro para o nó criado
rbno_t* criano(int chave, char letra){
    
    rbno_t *no;
    no=malloc(sizeof(rbno_t));
    if (!no){
        perror("Erro de alocação\n");
        return NULL;
    };

    no->chave=chave;
    no->letra=letra;
    no->cor= VERMELHO;

    no->p=NULL;
    no->esq=NULL;
    no->dir=NULL;

    return no;
}//cria no

void rotDireita(rbno_t *p){
    rbno_t* q=p->esq;
    q->p=p->p; 
    if(q->p!=NULL){
        if(q->p->esq==p)
            q->p->esq=q;
        else    
            q->p->dir=q;
    }

    p->esq=q->dir;
    if(p->esq!=NULL)
        p->esq->p=p;

    q->dir=p;
    p->p=q;
}

void rotEsquerda(rbno_t *p){
    rbno_t* x=p->dir;
    x->p=p->p;
    if(p->p!=NULL){     
        if(p->p->esq==p)
            p->p->esq=x;
        else    
            p->p->dir=x;
    }

    p->dir=x->esq;
    if(x->esq!=NULL)
        x->esq->p=p;
    
    p->p=x;
    x->esq=p; 
}

//ajusta a inclusão na RB garantindo o balanceamento
void arruma_rb (rb_t* arv, rbno_t* nooriginal){

    rbno_t *tio, *avo, *no=nooriginal;
    
    while (no->p != NULL && no->p->cor == VERMELHO){        //no não é raiz e pai é vermelho
        
        avo=no->p->p;
        if(no->p==avo->esq){                      //pai é filho da esq            
            
            tio=avo->dir;       //tio 
            if(tio!=NULL && tio->cor==VERMELHO){    
                //só recolorir para a direita
                no->p->cor=PRETO;
                avo->cor=VERMELHO;
                tio->cor=PRETO;    

                no=avo;
            }
            else{
                //pai da esquerda e no da direita
                if(no==no->p->dir){        
                    rotEsquerda(no->p);
                    no=no->esq;
                    avo=no->p->p;
                }
                //pai da esquerda e nó da esquerda
                rotDireita(avo);
                avo->cor=VERMELHO;
                no->p->cor=PRETO;
                if(no->p->p!=NULL)
                    arruma_rb(arv, no->p->p);
                else
                    arv->raiz=no->p;
            }
        }
        else{                                   //pai é filho da direita
            
            tio=avo->esq;       //tio
            if(tio!=NULL && tio->cor==VERMELHO){
                //recolorir para a esquerda
                no->p->cor=PRETO;
                avo->cor=VERMELHO;
                tio->cor=PRETO; 

                no=avo;
            }
            else{       
                if(no==no->p->esq){      //no é da esq com pai a direita
                    rotDireita(no->p);
                    no=no->dir;
                    avo=no->p->p;
                }
                //no da dir com pai a direita
                rotEsquerda(avo);
                avo->cor=VERMELHO;
                no->p->cor=PRETO;
                if(no->p->p!=NULL)
                    arruma_rb(arv, no->p->p);
                else
                    arv->raiz=no->p;
            }
        }
    }//while
    
    arv->raiz->cor = PRETO;
}

//Cria um nó com os valores passados e inclui na arvore, não inclui valores repetidos
int inclui_rb(rb_t* arv, int chave, char letra){
   
    if(arv->raiz==NULL){         //inclui na raiz
        arv->raiz=criano( chave, letra);
        if(arv->raiz==NULL)
            return 0;

        arv->raiz->cor=PRETO;   
        return 1;     
    }

    rbno_t *aux=arv->raiz, *p, *novoNo;

    while (aux != NULL){
        p=aux;
        
        if ( chave < aux->chave)
            aux=aux->esq;
        else{
            if(chave > aux->chave)
            aux=aux->dir;
            else 
                return 0;
        }
    }

    novoNo=criano( chave, letra);
    if(novoNo==NULL)
            return 0;

    if (chave < p->chave)
        p->esq = novoNo;
    else
        p->dir =novoNo;

    novoNo->p=p;

    arruma_rb(arv,novoNo);
    return 1;
}

//imprime toda a arvore
void leitura_rb_interno(struct rbno* no){
    if (no->esq != NULL)
        leitura_rb_interno(no->esq);
    
    printf("Chave:%d\n",no->chave);
    printf("Letra:%c\n",no->letra);

    if(no->cor==VERMELHO)
        printf("Cor: Vermelho\n");
    else
        printf("Cor: Preto\n");
    if(no->p!=NULL)
        printf("p:%d\n",no->p->chave);
    else
        printf("RAIZ\n");
    
    printf("\n");
    
    if(no->dir != NULL)
        leitura_rb_interno(no->dir);

}

//chama a função que imprime toda a arvore
void leitura_rb(rb_t* no){
    if (no->raiz!=NULL)    
        leitura_rb_interno(no->raiz);
}

//recebe uma chave e busca ela na estrutura se achar retorna um char que corresponde a chave
//se não achar retorn '\0'
char busca_rb_interno(rbno_t* raiz, int chave){
    char letra;
    
    rbno_t* no=raiz;
    
    while(no!=NULL && no->chave!=chave){
        if(no->chave > chave)
            no=no->esq;
        else  
            no=no->dir;
    }
    if(no->chave == chave){
        letra=no->letra;
        return letra;
    }
    else
        return '\0';
}
char busca_rb(rb_t* arv, int chave){
    if(arv->raiz!=NULL)
        return busca_rb_interno(arv->raiz, chave);

    return '\0';
}