CFLAGS = -Wall -g -std=c99 # gerar "warnings" detalhados e infos de depuração
 
objs = beale.o libbeale.o librb.o liblista.o

# regra default (primeira regra)
all: beale
 
# regras de ligacao
beale:	$(objs)
 
# regras de compilação
beale.o:	beale.c
libbeale.o:	libbeale.c 
librb.o:	librb.c
liblista.o:	liblista.c
 
# remove arquivos temporários
clean:
	-rm -f $(objs) *~
 
# remove tudo o que não for o código-fonte
purge: clean
	-rm -f beale
