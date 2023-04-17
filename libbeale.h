/*
Biblioteca que inclui funções auxiliares ao beale.c

Autor: Davi Lazzarin
Data: 27/03/2023 
*/

#ifndef __LIBBEALE__
#define __LIBBEALE__

/*Checa todos os argumentos e retorna:
0 em caso de err0
1 em caso de encode
2 para decode com arquivo de chaves
3 para decode com livro cifra
*/
int checaarg(int argc, char **argv, char** cifra, char** chaves, char** original, char** codificado, char** decodificado);

//Printa na tela como devem ser as opções na entrada do programa
void argerror();

//Printa na tela como devem ser os argumentos e suas funções
void arghelp();

//abre os arquivos conforme opt
//retorna 0 em caso de erro e 1 em caso de sucesso
int abre_arquivos(FILE** file1, FILE** file2, FILE** file3, FILE** file4, char* nfile1, char* nfile2, char* nfile3, char* nfile4, int opt);

#endif