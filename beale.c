#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include<wchar.h>
#include"libargmain.h"
#include"librb.h"

#define MAXTAMSTRG 1000
typedef wchar_t char_t;

int main(int argc, char **argv){

    int narg=checaarg(argc, argv);
    setlocale(LC_ALL, "");

    switch (narg)
    {
        case 1:                                    //ENCODE
            /*
            printf("ENCODE\n");
            printf("Nome do Livro: %s\n",argv[3]);              //nome do livro
            printf("Mensagem Original: %s\n",argv[5]);          //Mensagem Original
            printf("Nome da Saida Codificada: %s\n",argv[7]);   //Mensagem Codificada
            printf("Nome do Arquivo de Chaves: %s\n",argv[9]);  //nome do Arquivo de Chaves
            */
            
            break;
    case 2:
        //decode arquivo de chaves
        printf("Nome do Arquivo Codificado: %s\n",argv[3]);//nome do arquivo codificado
        printf("Nome da Saida Decodificada: %s\n",argv[7]);//Mensagem Decodificada
        printf("Nome do Arquivo de Chaves: %s\n",argv[5]);//nome do arquivo de chaves
        printf("DECODE");
        break;
    case 3:
        //decode livro cifras
        // printf("Nome do Arquivo Codificado: %s\n",argv[3]);//nome do arquivo codificado
        // printf("Nome da Saida Decodificada: %s\n",argv[7]);//Mensagem Decodificada
        // printf("Nome do Livro: %s\n",argv[5]);//nome do livro
        // printf("DECODE");
        FILE *livro=fopen(argv[5], "r");                            //abre o livro cifra
        if(!livro){
            perror("Erro ao abrir livro cifra");
            return 1;
        }//fopen livro

        FILE *arqsaida=fopen(argv[7],"w+");                        //abre a o arquivo de saida
        if(!arqsaida){
            perror("Erro ao abrir arquivo de saida");
            return 1;
        }//fopen arqsaida

        FILE *arqentrada=fopen(argv[3],"r");                      //abre a o arquivo de entrada
        if(!arqentrada){
            perror("Erro ao abrir arquivo de entrada");
            return 1;
        }//fopen arqcentrada
        
        rb_t* arv=criarb();
        if(!arv){
            perror("Erro ao gerar estruturda de dados");
            return 1;
        }//gera a Red Black

        char palavra[MAXTAMSTRG], caractere;
        int i=0;
        //final das alocações 

        //Le o arquivo e gera a estrutura 
        while ( fscanf(livro, "%s", palavra) != EOF){       
            //printf("%d, %c\n",i, palavra[0]);             
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
    default:
        printf("ERROR");
        return 1;
        break;
    }
}//Main