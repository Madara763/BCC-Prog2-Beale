#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"libargmain.h"

#define MAXTAMSTRG 1000

int main(int argc, char **argv){

    int narg=checaarg(argc, argv);
    switch (narg)
    {
    case 1:
        //encode
        printf("Nome do Livro: %s\n",argv[3]);//nome do livro
        printf("Mensagem Original: %s\n",argv[5]);//Mensagem Original
        printf("Nome da Saida Codificada: %s\n",argv[7]);//Mensagem Codificada
        printf("Nome do Arquivo de Chaves: %s\n",argv[9]);//nome do Arquivo de Chaves
        printf("ENCODE\n");


        FILE *livro=fopen(argv[3], "r");
        if(!livro){
            perror("Erro ao abrir Livro Cifra");
            return 1;
        }
        char palavra[MAXTAMSTRG];
        int i=0;

        
        while ( fscanf(livro, "%s", palavra) != feof (livro)){// testa depois de tentar ler!
            
            printf("%s\n",palavra);
        }
        fclose(livro);
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
        printf("Nome do Arquivo Codificado: %s\n",argv[3]);//nome do arquivo codificado
        printf("Nome da Saida Decodificada: %s\n",argv[7]);//Mensagem Decodificada
        printf("Nome do Livro: %s\n",argv[5]);//nome do livro
        printf("DECODE");
        break;
    default:
        printf("ERROR");
        return 1;
        break;
    }
}//Main