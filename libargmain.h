/*
Biblioteca que inclui funções de checagem dos argumentos da função Main
e retorna alguns codigos conforme os argumentos dados.

Autor: Davi Lazzarin
Data: 27/03/2023 
*/

#ifndef __LIBARGMAIN__
#define __LIBARGMAIN__

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

#endif