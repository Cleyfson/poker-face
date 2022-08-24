#ifndef RODADA
#define RODADA

#include "jogador.hpp"
#include <cstring>
#include <iostream>

class rodada {
public:
    rodada()
    {
        tamanho = 0;
        vencedores = 0;
        montante = 0;
    };
    int GetTamanho()
    {
        return tamanho;
    };
    int GetVencedores()
    {
        return vencedores;
    };
    int GetMontante()
    {
        return montante;
    };
    bool Vazia()
    {
        return tamanho == 0;
    };
    virtual void InsereInicio(Jogador jogador) = 0;
    virtual Jogador RemoveInicio() = 0;
    virtual void Imprime() = 0;
    virtual void Limpa() = 0;

protected:
    int tamanho;
    int vencedores;
    int montante;
    int dinheiro_old[20];
};

class rodadaArranjo : public rodada {
public:
    rodadaArranjo()
        : rodada() {};
    void InsereInicio(Jogador jogador);
    Jogador RemoveInicio();
    void Pontuacao();
    void SetMao(Jogador novo, Carta mao[]);
    bool SetPote(int pote);
    bool SetAposta(Jogador novo, int aposta);
    void LimpaMao();
    void ResultadoFinal(FILE* arqw);
    void resetar();
    void Vencedor(FILE* arqw, bool sanidade);
    void Sanidade();
    void resetaSanidade();
    void Imprime();
    void Limpa();

private:
    static const int MAXTAM = 20;
    Jogador jogadores[MAXTAM];
};

#endif