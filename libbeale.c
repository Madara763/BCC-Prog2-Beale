/*
Biblioteca que inclui funções de checagem dos argumentos da função Main
e retorna alguns codigos conforme os argumentos dados.

Autor: Davi Lazzarin
Data: 27/03/2023 
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"libbeale.h"

#define ENCODE 1
#define CHAVES 2
#define CIFRAS 3

/*Chaga todos os argumentos e retorna:
0 em caso de erro
1 em caso de encode
2 para decode com arquivo de chaves
3 para decode com livro cifra

OPT:
    -e encode
        -o mensagem codificada
        -b nome do livro cifra
        -m mensagem original
        -c arquivo de chaves

    -d decode
        -b livro cifra
        -c arquivo de chaves
        -i mensagem codificada
        -o mensagem decodificada
    
*/
int checaarg(int argc, char **argv, char** cifra, char** chaves, char** original, char** codificado, char** decodificado){
    
    //testa quantidade de argumentos
    if(argc!=8 && argc!=10 && argc!=2){
        argerror();
        return 0;
    }

    //testa o --help
    if(argc==2){    
        if(strcmp(argv[1],"--help") == 0){
            arghelp();
            return 0;
        }
    }
         
    //armazena os nomes dos aquivos
    //livro cifra
    //arquivo de chaves
    //mesnsagem original
    //mensagem codificada
    //mensagem decodificada

    int i=0;
    *cifra=NULL;
    *chaves=NULL;
    *original=NULL;
    *codificado=NULL;
    *decodificado=NULL;

    //verifica se existem as flags -e ou -d
    while(strcmp(argv[i], "-e") != 0 && strcmp(argv[i], "-d") != 0 && i < argc ){
        i++;
    }

    //encode
    if(strcmp(argv[i], "-e") == 0){
        if (argc != 10){
            argerror();
            return 0;
        }
        
        for(i=1; i<argc-1; i++){
            if(strcmp(argv[i], "-b") == 0 && argv[i+1][0] != '-')      //livro cifras
                *cifra=argv[i+1];            
            
            if(strcmp(argv[i], "-c") == 0 && argv[i+1][0] != '-')     //arquivos de chaves
                *chaves=argv[i+1];
            
            if(strcmp(argv[i], "-m") == 0 && argv[i+1][0] != '-')     //mensagem original
                *original=argv[i+1];
            
            if(strcmp(argv[i], "-o") == 0 && argv[i+1][0] != '-')     //mensagem codificada
                *codificado=argv[i+1];
            
        }

        if((*cifra!=NULL) && (*chaves!=NULL) && (*original!=NULL) && (*codificado!=NULL) )
            return ENCODE;          
    }
    //decode
    else if(strcmp(argv[i], "-d") == 0){    
         if (argc != 8){
            argerror();
            return 0;
        }
        //armazena se o decode será com livro cifra ou arq chaves

        for(i=1; i<argc-1; i++){
            if(strcmp(argv[i], "-b") == 0 && argv[i+1][0] != '-')     //livro cifras
                *cifra=argv[i+1];
            
            if(strcmp(argv[i], "-c") == 0 && argv[i+1][0] != '-')     //arquivos de chaves
                *chaves=argv[i+1];
            
            if(strcmp(argv[i], "-o") == 0 && argv[i+1][0] != '-')     //mensagem decodificada
                *decodificado=argv[i+1];
            
            if(strcmp(argv[i], "-i") == 0 && argv[i+1][0] != '-')     //mensagem codificada
                *codificado=argv[i+1];
            
        }

        if((*codificado!=NULL) && (*decodificado!=NULL) ){
            if(*cifra!=NULL && *chaves == NULL)
                return CIFRAS;
            else if(*cifra==NULL && *chaves != NULL)
                return CHAVES;
        }
    }//while

    argerror();
    return 0;
}

//Printa na tela como devem ser as opções na entrada do programa
void argerror(){//Imprime como devem ser os argumentos 
    printf("Argumentos errados, excessivos ou insuficientes.\n");
    printf("./beale --help para informações.\n");
}

//imprime como devem ser os argumentos
void arghelp(){
    printf("\nArgumentos:");
    printf("\nCodificação:");
    printf("\n\t -e encode");
    printf("\n\t -b livro cifra, obrigatório");
    printf("\n\t -m mensagem original, obrigatório");
    printf("\n\t -o mensagem codificada, obrigatório");
    printf("\n\t -c arquivo de chaves, obrigatório");
    printf("\n");
    printf("\nDecodificação");
    printf("\n\t -d decode");
    printf("\n\t -i mensagem codificada, obrigatório");
    printf("\n\t -o mensagem decodificada, obrigatório");
    printf("\n\t -b livro cifra, opcional ao -c");
    printf("\n\t -c arquivo de chave, opcional ao -b");
    printf("\nAjuda:");
    printf("\n\t --help");
    printf("\nBeale V1.0\tPor Davi Lazzarin\n");
}

//abre os arquivos conforme opt
//retorna 0 em caso de erro e 1 em caso de sucesso
int abre_arquivos(FILE** file1, FILE** file2, FILE** file3, FILE** file4, char* nfile1, char* nfile2, char* nfile3, char* nfile4, int opt){
    
    switch (opt)
    {
    case 1: 
        //abre aquivos para encode
        *file1=fopen(nfile1, "r");
        *file2=fopen(nfile2, "r");
        *file3=fopen(nfile3, "w+");  
        *file4=fopen(nfile4, "w+");

        if((*file1 == NULL) || (*file2 == NULL) || (*file3 == NULL) || (*file4 == NULL) ) 
            return 0;  
        break;
    case 2: 
        //abre aquivos para decode com arquivo de chaves
        *file1=fopen(nfile1, "r");
        *file2=fopen(nfile2, "r");
        *file3=fopen(nfile3, "w+");  

        if((*file1 == NULL) || (*file2 == NULL) || (*file3 == NULL) ) 
            return 0;  
        break;
    case 3: 
        //abre aquivos para decode com cifras
        *file1=fopen(nfile1, "r");
        *file2=fopen(nfile2, "r");
        *file3=fopen(nfile3, "w+");  

        if((*file1 == NULL) || (*file2 == NULL) || (*file3 == NULL) ) 
            return 0;  
        break;
    default:
        break;
    }
    
    return 1; 
}

