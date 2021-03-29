#/**
#*
#* @File : makefile
#*
#*
#* @Synopsis : Makefile pour les TD/TP Systemes
#*
#**/
include ../include/INCLUDE_H
#
COMPILER = g++ -c -I$(INCLUDE) -Wall -O3 -Werror $*.cxx 

LIBBUILDER = mkdir -p ../lib; ar -cqs ../lib/libSys.a $*.o

#
# Edition de liens
#
$(nom).run : codeobjsyst $(nom).o 
	g++ -s -o $(nom).run $(nom).o -L../lib -lSys 
#
$(nom).o : $(nom).cxx $(CEXC_H) $(NSSYSTEME_H)
	$(COMPILER)
#
# Code Objet pour la bibliotheque Systemes
# 

codeobjsyst: nsSysteme.o
	touch codeobjsyst
#
nsSysteme.o : nsSysteme.cxx $(CEXC_H) $(NSSYSTEME_H)
	$(COMPILER); $(LIBBUILDER) 
#
# Nettoyage du repertoire courant : executables et fichiers .o
#
clean : 
	clear; rm -rf *.o *.run codeobjsyst ../lib -v *~ ../include/*~
#




