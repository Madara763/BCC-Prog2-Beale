# BCC-Prog2-Beale
Esse repositório foi criado durante a elaboração de um trabalho academico de Programação 2 do curso de Ciência da Computação na UFPR em 2023.

O enunciado pode ser encontrado em https://wiki.inf.ufpr.br/maziero/doku.php?id=prog2:cifras_de_baele e nele se encontram alguns requisitos e especificações do projeto.

Descrição:
O programa é composto por 8 arquivos sendo estes:
beale.c - Contém a função main, nele processamos os aquivos conforme os parametros recebidos e geramos os arquivos 
libbeale.c - Contém funções auxiliares ao beale.c, como tratamento de argumentos e abertura de arquivos
liblista.c - Implementa uma lista feita para suprir as necessidades desse trabalho, não tem a intenção de ser um TAD que possa ser usado em outros programas sem modificações
librb.c - implementa uma arvore RedBlack para otimização da decodificação, possui modificações especificas para esse trabalho
libbeale.h - header 
liblista.c - header
librb.c - header
Makefile - Arquivo make usado para a compilação do projeto

Observações: 
Quanto as funcionalidades:
    Os arquivos codificados ou decodificados pelo beale geram arquivos de saida com todas as letras em minusculo.
    Para acesar arquivos em outros diretórios o deve-se passar o caminho completo do arquivo na máquina

Quanto a algumas escolhas:
    A utilização da RedBlack se mostrou uma opção válida para redução do custo de busca em casos de decode após perceber que o programa poderia receber "livros cifra" com milhares de palavras, isso geraria um possivel custo O(n) = n durante as buscas, podendo ser reduzido a O(n) = Log(n) com a utilização da RB.
    Foi inevitável o uso de algum tipo de lista para a geração dos arquivos de chaves durante o encode, já que de alguma forma todos os numeros referentes a algum caractere deveriam estar ligados a ele, e a melhor forma para se fazer isso é com uma lista
