#ifndef JOGADORHPP
#define JOGADORHPP

#include "carta.hpp"
#include <cstring>
#include <iostream>

/* Classe Jogador */

class Jogador {
private:
    Carta cartas[5];
    std::string nome;
    std::string mao;
    int dinheiro;
    int pontos;

public:
    Jogador();
    Jogador(std::string nome, int dinheiro);
    int getPontos();
    std::string getNome();
    std::string getMao();
    void setMao(Carta mao[]);
    void setDinheiro(int montante);
    bool setAposta(int aposta);
    int getDinheiro();
    bool setPote(int pote);
    void imprime();
    void limpaMao();
    void zerarPontos();
    void pontuacao();
    void resetaDinheiro(int dinheiro);
};

#endif