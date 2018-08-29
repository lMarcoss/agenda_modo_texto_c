
CC = gcc
CFLAGS = -g -Wall
SRC = Agenda.c Listas.c Listas.h
OBJ = Agenda.o Listas.o

# Reglas explicitas

all: $(OBJ)
	$(CC) $(CFLAGS) -o Agenda $(OBJ)
clean:
	$(RM) $(OBJ) main

# Reglas implicitas

Listas.o: Listas.c Listas.h
Lista.o: Agenda.c Listas.h 
