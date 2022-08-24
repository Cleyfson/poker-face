#ifndef CARTA
#define CARTA

#include <iostream>

class Carta {
private:
    int valor;
    char naipe;

public:
    Carta();
    void setCarta(int valor, char naipe);
    int getValor() { return this->valor; };
    char getNaipe() { return this->naipe; };
    void imprime();

    friend class Jogador;
};

#endif