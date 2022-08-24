#include "carta.hpp"
#include "msgassert.hpp"

Carta::Carta()
// Descricao: construtor padrão de carta
// Entrada: não tem
// Saida: carta de valor 0 e naipe -
{
    this->valor = 0;
    this->naipe = '-';
};

void Carta::setCarta(int valor, char naipe)
// Descricao: seta o valor e naipe de uma carta
// Entrada: valor naipe
// Saida: carta
{
    if (valor == 1)
        this->valor = 14;
    else
        this->valor = valor;
    this->naipe = naipe;
};

void Carta::imprime()
// Descricao: imprime a carta na sequencia de seu valor e naipe seguido de um espaço
// Entrada: não tem
// Saida: impressao na saida padrao (stdout)
{
    std::cout << this->valor << this->naipe << " ";
};