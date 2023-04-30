#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include<ctype.h>

#include"libbeale.h"
#include"librb.h"
#include"liblista.h"

#define TAB_ASCII 256
#define MAXTAMSTRG 1000
#define ESPACO -1
#define NOVALINHA -2
#define ENDLINE -3

int main(int argc, char **argv){

    // Ponteiros para os nomes dos arquivos   
    char *nomeCifra, *nomeChaves, *nomeOriginal, *nomeCodificado, *nomeDecodificado;
    char palavra[MAXTAMSTRG], caractere;

    //nopt recebe o numero da opção que o programa executará:
    //1 encode
    //2 decode com livro de chaves
    //3 decode com livro cifras
    int nopt=checaarg(argc, argv, &nomeCifra, &nomeChaves, &nomeOriginal, &nomeCodificado, &nomeDecodificado);
    int i=1, codigo;
    
    FILE *livro, *arqentrada, *arqsaida, *arqchaves;
    livro=NULL;
    arqentrada=NULL;
    arqsaida=NULL;
    arqchaves=NULL;

    setlocale(LC_ALL, "");
    srand(time(NULL));

    switch (nopt)
    {
        case 1:{         //ENCODE                                    

            int arq=abre_arquivos(&livro, &arqentrada, &arqsaida, &arqchaves, nomeCifra,  nomeOriginal, nomeCodificado, nomeChaves, nopt);
            if(arq == 0){
                perror("Erro ao abrir arquivos");
                return 1;
            }

            lista_t* lista=cria_lista();
            if(!lista){
                perror("Erro ao Gerar Estrutura de Dados");
                return 1;
            }//fopen livro

            //Le o arquivo e gera a estrutura 
            while ( fscanf(livro, "%s", palavra) != EOF){
                
                if(palavra[0]>=0){  //para restringir caracteres estranhos 

                    if((palavra[0] > 64) && (palavra[0] < 91)  )    //para garantir que não haverá letras maiusculas
                        caractere=tolower(palavra[0]);
                    else
                        caractere=palavra[0];   

                    if((adiciona_lista(lista, caractere, i)) == 0 ){
                        perror("Erro ao Gerar Estrutura de Dados");
                        return 1;
                    }
                    i++;
                }
            }
            
            //Verifica a integridade da lista
            integra_lista(lista, i);

            //Gera o arquivo de Chaves
            imprime_lista(lista, arqchaves);

            //Lê a mensagem original e gera  a msg codificada
            caractere=getc(arqentrada);
            if((caractere > 64) && (caractere < 91)  )
                caractere=tolower(caractere);
            while (!feof(arqentrada)){
                
                if (caractere == ' ' )
                    fprintf(arqsaida,"%d ", ESPACO);
        
                else if (caractere == '\n' ){
                    fprintf(arqsaida,"%d ", NOVALINHA);
                }
                else if (caractere == '\0' ){
                    fprintf(arqsaida,"%d ", ENDLINE);
                }
                else{
                    codigo=busca_cod_lista(lista, caractere);
                    if(codigo != -1)                                           
                        fprintf(arqsaida,"%d ", codigo);                         
                }
                
                caractere=getc(arqentrada);
                if((caractere > 64) && (caractere < 91)  )
                    caractere=tolower(caractere);

            }

            //Libera memória e fecha os arquivos
            deleta_lista(lista);
            lista=NULL;
            fclose(arqsaida);
            arqsaida=NULL;
            fclose(arqentrada);
            arqentrada=NULL;
            fclose(arqchaves);
            arqchaves=NULL;
            fclose(livro);
            livro=NULL;
            break;
        }
        case 2:{        //DECODE ARQUIVO DE CHAVES

            int arq=abre_arquivos(&arqentrada, &arqchaves, &arqsaida, NULL,  nomeCodificado, nomeChaves, nomeDecodificado, NULL,  nopt);
            if(arq == 0){
                perror("Erro ao abrir arquivos");
                return 1;
            }

            rb_t* arv=criarb();  
            if(!arv){
                perror("Erro ao gerar estrutura de dados");
                return 1;
            }//gera a Red Black
            //FINAL DAS ALOCAÇÕES

            //le o arquivo de chave e gera a estrutura 
            while (fscanf(arqchaves, "%s", palavra) != EOF ){

                if(palavra[1] == ':')   //atualiza caractere, linha nova
                    if((palavra[0] > 64) && (palavra[0] < 91)  )
                        caractere=tolower(palavra[0]);
                    else
                        caractere=palavra[0];
                else{
                    i=atoi(palavra);
                    caractere=tolower(caractere);
                    inclui_rb(arv, i, caractere);
                }
            }

            //Le a estrutura e gera a saida
            while (fscanf(arqentrada, "%s", palavra) != EOF){
                i=atoi(palavra);
                if(i<=0){
                    if(i==ESPACO)
                       fprintf(arqsaida,"%c", ' ');
                    else if (i== ENDLINE)
                         fprintf(arqsaida,"%c", '\0'); 
                    else if (i== NOVALINHA)
                        fprintf(arqsaida,"%c", '\n');

                }
                else{
                    caractere=busca_rb(arv, i);
                    if((palavra[0] > 64) && (palavra[0] < 91)  )
                        caractere=tolower(palavra[0]);
                    
                    if(caractere != '\0')
                        fprintf(arqsaida,"%c",caractere); 
                }          
            }

            //Libera memória e fecha os arquivos
            deleta_rb(arv);
            arv=NULL;
            fclose(arqentrada);
            arqentrada=NULL;
            fclose(arqsaida);
            arqsaida=NULL;
            fclose(arqchaves);
            arqchaves=NULL;
            break;
        }
        case 3:{            //DECODE LIVRO CIFRAS
            
            //Para a integralização da estrutura
            char l[TAB_ASCII];    
            int j;
            for(j=0; j<256; j++)
                l[j]='0';

            int arq=abre_arquivos(&arqentrada, &livro, &arqsaida, NULL,  nomeCodificado, nomeCifra, nomeDecodificado, NULL,  nopt);
            if(arq == 0){
                perror("Erro ao abrir arquivos");
                return 1;
            }
                
            rb_t* arv=criarb();                                           
            if(!arv){
                perror("Erro ao gerar estrutura de dados");
                return 1;
            }//gera a Red Black
            //FINAL DAS ALOCAÇÕES

            //Le o arquivo e gera a estrutura 
            while ( fscanf(livro, "%s", palavra) != EOF){

                if((palavra[0] > 64) && (palavra[0] < 91)  )
                        caractere=tolower(palavra[0]);
                else
                    caractere=palavra[0];

                if(caractere>=0){
                    inclui_rb(arv, i, caractere);
                    i++;

                //salva os caracteres diferentes que apareceram na lista
                if(caractere>32 && caractere<256){
                    j=caractere;
                    if(l[j]=='0')
                        l[j]='1';
                }
                }
            }

            //integra a rb, garantindo que todos os char estarão na estrutura
            integra_rb( arv, l, i);

            //Le a estrutura e gera a saida
            while (fscanf(arqentrada, "%s", palavra) != EOF){
                i=atoi(palavra);
                if(i<=0){
                    if(i==ESPACO)
                       fprintf(arqsaida,"%c", ' ');
                    else if (i== ENDLINE)
                         fprintf(arqsaida,"%c", '\0'); 
                    else if (i== NOVALINHA)
                        fprintf(arqsaida,"%c", '\n');
                }
                else{
                    caractere=busca_rb(arv, i);
                    caractere=tolower(caractere);
                    if(caractere != '\0')
                        fprintf(arqsaida,"%c",caractere); 
                }          
            }
            
            //Libera memória e fecha os arquivos
            deleta_rb(arv);
            arv=NULL;
            fclose(arqentrada);
            arqentrada=NULL;
            fclose(arqsaida);
            arqsaida=NULL;
            fclose(livro);
            livro=NULL;
            break;
        }
        default:
            return 1;

    }//switch
    return 0;
    
}//Main