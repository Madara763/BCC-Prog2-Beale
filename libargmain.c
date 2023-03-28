/*
Biblioteca que inclui funções de checagem dos argumentos da função Main
e retorna alguns codigos conforme os argumentos dados.

Autor: Davi Lazzarin
Data: 27/03/2023 
*/
#include<stdio.h>
#include<stdlib.h>
#include"libargmain.h"


/*Chaga todos os argumentos e retorna:
0 em caso de err0
1 em caso de encode
2 para decode com arquivo de chaves
3 para decode com livro cifra
*/
int checaarg(int argc, char **argv){
    if(argc!=8 && argc!=10){
        argerror();
        return 0;
    }
    if(argv[1][1]=='d'){//Argumento para decodificar

        if(argv[6][1]=='o'){
           
            if(argv[4][1]=='c')//decoder usando arquivo de chaves
                return 2;

            else if(argv[4][1]=='b')//decoder usando livro de cifras
                return 3;
            
        }else{
            argerror();
            return 0;
        } 

    }else if(argv[1][1]=='e'){//Argumento para codificar
        if(argv[2][1]=='b' && argv[4][1]=='m' && argv[6][1]=='o' && argv[8][1]=='c')
            return 1;
        
    }else{
        argerror();
        return 0;
    }
    return 0;
}

//Printa na tela como devem ser as opções na entrada do programa
void argerror(){//Imprime como devem ser os argumentos 
    printf("Argumentos excessivos ou insuficientes.\n");
    printf("Tente\n\t -d = Decodificar\n\t -e = Codificar\n\t -i = Nome Mesagem Codificada\n");
    printf("\t -b = Livro Cifra\n\t -c = Aruivo de Chaves\n\t -o = Nome Mesagem Decodificada\n\t -m = Mensagem Original\n");     
}