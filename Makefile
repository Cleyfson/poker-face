CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/tp1.o $(OBJ)/carta.o $(OBJ)/jogador.o $(OBJ)/rodada.o $(OBJ)/memlog.o
HDRS = $(INC)/carta.hpp $(INC)/jogador.hpp $(INC)/rodada.hpp $(INC)/msgassert.hpp $(INC)/memlog.hpp
CFLAGS = -pg -Wall -c -I$(INC)
# ANALISAMEM = ../analisamem/bin/analisamem

EXE = $(BIN)/tp1

run: $(EXE)
	$(EXE) -p arquivo.out
	

all:$(EXE)

$(BIN)/tp1: $(OBJS)
	$(CC) -pg -o $(BIN)/tp1 $(OBJS) $(LIBS)

$(OBJ)/tp1.o: $(HDRS) $(SRC)/tp1.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/tp1.o $(SRC)/tp1.cpp 	

$(OBJ)/rodada.o: $(HDRS) $(SRC)/rodada.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/rodada.o $(SRC)/rodada.cpp 

$(OBJ)/jogador.o: $(HDRS) $(SRC)/jogador.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/jogador.o $(SRC)/jogador.cpp 

$(OBJ)/carta.o: $(HDRS) $(SRC)/carta.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/carta.o $(SRC)/carta.cpp 
	
$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.cpp 
	
clean:
	rm -f  saida.txt arquivo.out gmon.out $(BIN)/tp1 $(OBJS)
