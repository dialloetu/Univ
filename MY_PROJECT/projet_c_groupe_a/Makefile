CC=gcc
CFLAGS=-O2 -W `sdl-config --cflags` -g
LDLIBS=`sdl-config --libs` -lm -lSDL_ttf -g
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o) 
EXEC=main

#Modification de la police
#changeFont : 
#		sed 


#Exécution du projet :

run : all
	./$(EXEC) &

#Construction du projet :

all : $(EXEC)

#Edition de liens :

$(EXEC): $(OBJ) graphics.o
	$(CC)  -o $@  $^ $(LDLIBS)

#Compilation séparé :

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) 

main.o: Interface.h controleur.h
Interface.o: Interface.h
controleur.o: modele.h Interface.h

#Suppression des fichiers générés :

clean : 
	rm -f $(EXEC)
	rm -f *.o

