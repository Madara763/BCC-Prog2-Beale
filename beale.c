#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

#include"libargmain.h"
#include"librb.h"

#define MAXTAMSTRG 1000

int main(int argc, char **argv){

    // Ponteiros para os nomes dos arquivos
    // cifra
    // chaves
    // original
    // codificado
    // decodificado
    
    char *cifra, *chaves, *original, *codificado, *decodificado;
    char palavra[MAXTAMSTRG], caractere;

    int narg=checaarg(argc, argv, &cifra, &chaves, &original, &codificado, &decodificado);
    int i=0;
    
    setlocale(LC_ALL, "");

    switch (narg)
    {
        case 1:{         //ENCODE                                    
               
            printf("ENCODE\n");
            printf("Nome do Livro: %s\n",cifra);              //nome do livro
            printf("Mensagem Original: %s\n",original);          //Mensagem Original
            printf("Nome da Saida Codificada: %s\n",codificado);   //Mensagem Codificada
            printf("Nome do Arquivo de Chaves: %s\n",chaves);  //nome do Arquivo de Chaves
               
            break;
        }
        case 2:{        //DECODE ARQUIVO DE CHAVES

            FILE *livro=fopen(chaves, "r");                                 //abre o arquivo de chaves
            if(!livro){
                perror("Erro ao abrir livro cifra");
                return 1;
            }//fopen livro

            FILE *arqsaida=fopen(decodificado,"w+");                        //abre a o arquivo de saida
            if(!arqsaida){
                perror("Erro ao abrir arquivo de saida");
                return 1;
            }//fopen arqsaida

            FILE *arqentrada=fopen(codificado,"r");                         //abre a o arquivo de entrada
            if(!arqentrada){
                perror("Erro ao abrir arquivo de entrada");
                return 1;
            }//fopen arqcentrada

            rb_t* arv=criarb();                                             //cria a arvore
            if(!arv){
                perror("Erro ao gerar estrutura de dados");
                return 1;
            }//gera a Red Black
            //final das alocações 

            //le o arquivo de chave e gera a estrutura 
            while (fscanf(livro, "%s", palavra) != EOF ){
                if(palavra[1] == ':')   //atualiza caractere, linha nova
                    caractere=palavra[0];
                else{
                    i=atoi(palavra);
                    inclui_rb(arv, i, caractere);
                }
            }
            
            //Le a estrutura e gera a saida
            while (fscanf(arqentrada, "%s", palavra) != EOF){
                i=atoi(palavra);
                if(i==-1){
                    fprintf(arqsaida," ");   
                }
                else{
                    caractere=busca_rb(arv, i);
                    if(caractere != '\0')
                        fprintf(arqsaida,"%c",caractere); 
                }          
            }

            deleta_rb(arv);
            fclose(arqentrada);
            fclose(arqsaida);
            fclose(livro);
            break;
        }
        case 3:{            //DECODE LIVRO CIFRAS
        
            FILE *livro=fopen(cifra, "r");                                   //abre o livro cifra
            if(!livro){
                perror("Erro ao abrir livro cifra");
                return 1;
            }//fopen livro

            FILE *arqsaida=fopen(decodificado,"w+");                         //abre a o arquivo de saida
            if(!arqsaida){
                perror("Erro ao abrir arquivo de saida");
                return 1;
            }//fopen arqsaida

            FILE *arqentrada=fopen(codificado,"r");                          //abre a o arquivo de entrada
            if(!arqentrada){
                perror("Erro ao abrir arquivo de entrada");
                return 1;
            }//fopen arqcentrada
        
            rb_t* arv=criarb();                                              //cria a arvore
            if(!arv){
                perror("Erro ao gerar estrutura de dados");
                return 1;
            }//gera a Red Black
            //final das alocações 


            //Le o arquivo e gera a estrutura 
            while ( fscanf(livro, "%s", palavra) != EOF){                   
                inclui_rb(arv, i, palavra[0]);
                i++;
            }

            //Le a estrutura e gera a saida
            while (fscanf(arqentrada, "%s", palavra) != EOF){
                i=atoi(palavra);
                if(i==-1){
                    fprintf(arqsaida," ");   
                }
                else{
                    caractere=busca_rb(arv, i);
                    if(caractere != '\0')
                        fprintf(arqsaida,"%c",caractere); 
                }          
            }

            //Libera memória e fecha os arquivos
            deleta_rb(arv);
            fclose(arqentrada);
            fclose(arqsaida);
            fclose(livro);
            break;
        }
        default:
            return 1;

    }//switch
    return 0;
    
}//Main