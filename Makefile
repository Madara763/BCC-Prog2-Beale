CFLAGS = -Wall -g  # gerar "warnings" detalhados e infos de depuração
 
objs = beale.o libargmain.o

# regra default (primeira regra)
all: beale
 
# regras de ligacao
beale:	$(objs)
 
# regras de compilação
beale.o:	beale.c
libargmain.o:	libargmain.c 
 
# remove arquivos temporários
clean:
	-rm -f $(objs) *~
 
# remove tudo o que não for o código-fonte
purge: clean
	-rm -f beale
