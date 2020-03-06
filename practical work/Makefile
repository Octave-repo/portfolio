# Makefile pour le tp de développement d'applications 
COMPIL := gcc #Le compilateur
FLAG := -Wall -Wextra -pedantic #Les flags a utiliser

all : compile

clean :
	rm -f a.out
	rm -f prototype.h.gch

compile :
	$(COMPIL) parti1.c parti2.c prototype.h main.c $(FLAG)

run :
	@($(COMPIL) parti1.c parti2.c prototype.h main.c $(FLAG))
	@(./a.out)
	@(rm -f a.out)