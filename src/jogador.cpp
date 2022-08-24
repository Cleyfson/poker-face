#include "jogador.hpp"
#include "msgassert.hpp"
#include <iostream>

void troca(Carta* a, Carta* b)
// Descricao: troca duas cartas de posicao na mão de um jogador
// Entrada: Carta *a , Carta *b
// Saida: Carta a e Carta b em posições trocadas
{
    Carta temp = *a;
    *a = *b;
    *b = temp;
}

int dividir(Carta cartas[], int esq, int dir)
// Descricao: divide a mão do jogador em duas partes
// Entrada: Carta cartas[], int esq, int dir
// Saida: Carta cartas[], int esq, int dir
{
    Carta pivot = cartas[dir];
    int i = (esq - 1);
    for (int j = esq; j < dir; j++) {
        if (cartas[j].getValor() <= pivot.getValor()) {
            i++;
            troca(&cartas[i], &cartas[j]);
        }
    }
    troca(&cartas[i + 1], &cartas[dir]);
    return (i + 1);
}

void quickSort(Carta cartas[], int esq, int dir)
// Descricao: ordenada a mão dos jogadores
// Entrada: Carta cartas[], int esq, int dir
// Saida: Carta cartas[] de forma ordenada
{
    if (esq < dir) {
        int pi = dividir(cartas, esq, dir);
        quickSort(cartas, esq, pi - 1);
        quickSort(cartas, pi + 1, dir);
    }
}

Jogador::Jogador()
// Descricao: construtor padrão da classe jogador
// Entrada: nao tem
// Saida: Jogador de nome "", com mao "", dinheiro 0 e pontos 0
{
    this->nome = "";
    this->mao = "";
    this->dinheiro = 0;
    this->pontos = 0;
};

Jogador::Jogador(std::string nome, int dinheiro)
// Descricao: seta um novo jogador
// Entrada: nome, dinheiro
// Saida: Jogador
{
    this->nome = nome;
    this->dinheiro = dinheiro;
};

int Jogador::getDinheiro()
// Descricao: retorna o total de dinheiro de um jogador
// Entrada: nao tem
// Saida: dinheiro
{
    return dinheiro;
}

std::string Jogador::getNome()
// Descricao: retorna o nome de um jogador
// Entrada: nao tem
// Saida: nome
{
    return nome;
}

std::string Jogador::getMao()
// Descricao: retorna o tipo de mao de um jogador, ex: HC, OP, TK
// Entrada: nao tem
// Saida: mao
{
    return mao;
}

int Jogador::getPontos()
// Descricao: retorna o total de pontos de um jogador, relacionada a mao dele
// Entrada: nao tem
// Saida: pontos
{
    return pontos;
}

void Jogador::imprime()
// Descricao: imprime os dados de um jogador
// Entrada: nao tem
// Saida: impressao na saida padrao (stdout)
{
    std::cout << this->nome << " " << this->dinheiro << " ";
    for (int i = 0; i < 5; i++) {
        this->cartas[i].imprime();
    }
    std::cout << this->pontos << std::endl;
};

void Jogador::setMao(Carta mao[])
// Descricao: seta a cartas da mao de um jogador
// Entrada: vetor de cartas mao
// Saida: vetor de cartas da mão do jogador
{
    this->pontos = 0;
    for (int i = 0; i < 5; i++) {
        this->cartas[i] = mao[i];
    }
};

void Jogador::resetaDinheiro(int dinheiro)
// Descricao: retorna o dinheiro do jogador para o estagio anterior ao ativamento da sanidade
// Entrada: dinheiro
// Saida: dinheiro
{
    this->dinheiro = dinheiro;
};

bool Jogador::setAposta(int aposta)
// Descricao: set a aposta de um jogador
// Entrada: aposta
// Saida: dinheiro do jogador decrescido do valor da aposta
{
    bool sanidade = (dinheiro <= 0);
    // aviso de que a sanidade do jogador foi quebrada e partida invalidada
    avisoAssert((dinheiro > 0), "sanidade quebrada, partida invalidada");
    this->dinheiro -= aposta;

    return sanidade;
};

bool Jogador::setPote(int pote)
// Descricao: set o pingo de um jogador
// Entrada: pote
// Saida: dinheiro do jogador decrescido do valor do pingo
{
    bool sanidade = (dinheiro <= 0);
    // aviso de que a sanidade do jogador foi quebrada e partida invalidada
    avisoAssert((dinheiro > 0), "sanidade quebrada, partida invalidada");
    this->dinheiro -= pote;

    return sanidade;
};

void Jogador::setDinheiro(int montante)
// Descricao: seta o dinheiro do jogador vencedor
// Entrada: montante
// Saida: dinheiro do jogador acrescido do valor do montante
{
    this->dinheiro += montante;
}

void Jogador::limpaMao()
// Descricao: limpa a mao dos jogadores apos o fim de uma rodada
// Entrada: nao tem
// Saida: mao do jogadores com valor = 0 e naipe = '-'
{
    this->pontos = 0;
    for (int i = 0; i < 5; i++) {
        this->cartas[i].setCarta(0, '-');
    }
};

bool flush(Carta cartas[])
// Descricao: testa se as cartas da mao de um jogador tem o mesmo naipe
// Entrada: vetor cartas
// Saida: true ou false
{
    int first = (cartas[0].getNaipe() == cartas[1].getNaipe());
    int second = (cartas[1].getNaipe() == cartas[2].getNaipe());
    int third = (cartas[2].getNaipe() == cartas[3].getNaipe());
    int fourth = (cartas[3].getNaipe() == cartas[4].getNaipe());

    if (first && second && third && fourth) {
        return true;
    } else {
        return false;
    }
};

bool straight(Carta cartas[])
// Descricao: testa se as cartas da mao de um jogador são uma sequencia
// Entrada: vetor cartas
// Saida: true ou false
{
    int first = 0;
    int second = 0;
    int third = 0;
    int fourth = 0;

    // teste o caso unico, onde o as vale 1, numa sequencia
    if (cartas[0].getValor() == 2 && cartas[1].getValor() == 3 && cartas[2].getValor() == 4 && cartas[3].getValor() == 5 && cartas[4].getValor() == 14) {
        return true;
    } else {

        first = (cartas[0].getValor() == cartas[1].getValor() - 1);
        second = (cartas[1].getValor() == cartas[2].getValor() - 1);
        third = (cartas[2].getValor() == cartas[3].getValor() - 1);
        fourth = (cartas[3].getValor() == cartas[4].getValor() - 1);
    }

    if (first && second && third && fourth) {
        return true;
    } else {
        return false;
    }
};

void Jogador::zerarPontos()
// Descricao: zeram os ponto de um jogador após o fim da rodada
// Entrada: nao tem
// Saida: pontos = 0
{
    pontos = 0;
};

void Jogador::pontuacao()
// Descricao: testa os diferentes cenarios para o tipo de mao que um jogador possui, baseado em suas cartas
// Entrada: nao tem
// Saida: tipo de mao do jogador
{
    int value = 0;

    // testa se as cartas avalidas tem naipe e valor não nulos
    if (cartas[0].naipe != '-' && cartas[0].valor != 0) {

        // ordenada as cartas em ordem crescente baseado em ser valor
        quickSort(cartas, 0, 4);

        // testa se as mao tem pares nas 4 posições possiveis diferentes
        int first_pair = (cartas[0].valor == cartas[1].valor);
        int second_pair = (cartas[1].valor == cartas[2].valor);
        int third_pair = (cartas[2].valor == cartas[3].valor);
        int fourth_pair = (cartas[3].valor == cartas[4].valor);
        if (first_pair || second_pair || third_pair || fourth_pair) {
            if (first_pair) {
                value = cartas[0].valor;
            } else if (second_pair) {
                value = cartas[1].valor;
            } else if (third_pair) {
                value = cartas[2].valor;
            } else if (fourth_pair) {
                value = cartas[3].valor;
            }

            // se os pares forem encontrados a pontuação do jogador e seu tipo de mão sera atualizado
            pontos = 1000 + (3 * value);
            mao = "OP";
        }

        // testa se as mao tem dois pares nas 2 posições possiveis diferentes
        int first_two_pair = (first_pair && !second_pair && third_pair);
        int second_two_pair = (second_pair && !third_pair && fourth_pair);
        int third_two_pair = (first_pair && !second_pair && !third_pair && fourth_pair);
        if (first_two_pair || second_two_pair || third_two_pair) {
            if (first_two_pair) {
                value = cartas[0].valor + cartas[2].valor;
            } else if (second_two_pair) {
                value = cartas[1].valor + cartas[3].valor;
            } else if (third_two_pair) {
                value = cartas[0].valor + cartas[3].valor;
            }

            // se os dois pares forem encontrados a pontuação do jogador e seu tipo de mão sera atualizado
            pontos = 2000 + (3 * value);
            mao = "TP";
        }

        // testa se as mao tem trincas nas 3 posições possiveis diferentes
        int first_three = (first_pair && second_pair);
        int second_three = (second_pair && third_pair);
        int third_three = (third_pair && fourth_pair);
        if (first_three || second_three || third_three) {
            if (first_three) {
                value = cartas[0].valor;
            } else if (second_three) {
                value = cartas[1].valor;
            } else if (third_pair) {
                value = cartas[2].valor;
            }

            // se as trincas forem encontrados a pontuação do jogador e seu tipo de mão sera atualizado
            pontos = 3000 + (3 * value);
            mao = "TK";
        }

        // testa se a mao é uma sequencia
        if (straight(this->cartas)) {
            // se as sequencias forem encontrados a pontuação do jogador e seu tipo de mão sera atualizado
            pontos = 4000;
            mao = "S";
        }

        // testa se a mao e um flush
        if (flush(this->cartas)) {
            // se o flush forem encontrados a pontuação do jogador e seu tipo de mão sera atualizado
            pontos = 5000;
            mao = "F";
        }

        // testa se a mao tem full houses nas 2 posicão diferentes possiveis
        int first_full_house = (first_pair && third_three);
        int second_full_house = (first_three && fourth_pair);
        if (first_full_house || second_full_house) {
            if (first_full_house) {
                value = cartas[2].valor;
            } else if (second_full_house) {
                value = cartas[0].valor;
            }

            // se o fullhouse for encontrados a pontuação do jogador e seu tipo de mão sera atualizado
            pontos = 6000 + (3 * value);
            mao = "FH";
        }

        // testa se a mao tem quadras nas 2 posicão diferentes possiveis
        int first_four = (first_three && second_three);
        int second_four = (second_three && third_three);
        if (first_four || second_four) {
            if (first_four) {
                value = cartas[0].valor;
            } else if (second_four) {
                value = cartas[1].valor;
            }

            // se as quadras forem encontrados a pontuação do jogador e seu tipo de mão sera atualizado
            pontos = 7000 + (3 * value);
            mao = "FK";
        }

        // testa se a mao tem um straight flush
        if (straight(this->cartas) && flush(this->cartas)) {

            // se o straight flush for encontrado a pontuação do jogador e seu tipo de mão sera atualizado
            pontos = 8000;
            mao = "SF";
        }

        // testa se a mao tem um royal straight flush
        if (straight(this->cartas) && flush(this->cartas) && cartas[0].valor == 10) {

            // se o royal straight flush for encontrado a pontuação do jogador e seu tipo de mão sera atualizado
            pontos = 9000;
            mao = "RSF";
        }

        // caso a mao do jogador não passe em nenhum dos testes anteriores, sua mão sera declarada com tipo maior carta
        if (mao == "")
            mao = "HC";

        // resolve algumas dos problemas relacionados ao valor do A's no straight e straight flush
        if ((mao == "S" || mao == "SF") && cartas[3].getValor() == 5 && cartas[4].getValor() == 14)
            pontos += 1;
        else
            pontos += cartas[4].valor;
    }
};
