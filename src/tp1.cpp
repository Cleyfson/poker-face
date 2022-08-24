#include "memlog.hpp"
#include "rodada.hpp"
#include <fstream>
#include <getopt.h>
#include <iostream>
#include <msgassert.hpp>
#include <sstream>

// Variaveis Globais
Carta mao[5];
char nome[50];
int aposta;
char lognome[100];
int regmem;
int memlog;

void uso()
// Descricao: imprime as opcoes de uso
// Entrada: nao tem
// Saida: impressao das opcoes de linha de comando
{
    fprintf(stderr, "\t-p <arq>\t(arquivo de registro de acesso)\n");
    fprintf(stderr, "\t-l \t(registrar acessos a memoria)\n");
}

void parse_args(int argc, char** argv)
// Descricao: le as opcoes da linha de comando e inicializa variaveis
// Entrada: argc e argv
// Saida: optescolhida, regmem, lognome, m1nome, m2nome, m3nome
{
    // variaveis externas do getopt
    extern char* optarg;

    // variavel auxiliar
    int c;

    // inicializacao variaveis globais para opcoes
    regmem = 0;
    memlog = 0;
    lognome[0] = 0;

    // getopt - letra indica a opcao, : junto a letra indica parametro
    // no caso de escolher mais de uma operacao, vale a ultima
    while ((c = getopt(argc, argv, "p:l")) != EOF)
        switch (c) {
        case 'p':
            memlog = 1;
            strcpy(lognome, optarg);
            break;
        case 'l':
            regmem = 1;
            break;
        default:
            uso();
            exit(1);
        }
    // verificacao da consistencia das opcoes
    avisoAssert(strlen(lognome) > 0, "tp1 - nome de arquivo de registro de acesso tem que ser definido");
}

void leNomeAposta(FILE* arq)
// Descricao: Le o nome e aposta dos jogadores que estão no arquivo entrada.txt
// Entrada: nome do arquivo de entrada
// Saida: nome, aposta
{

    fscanf(arq, "\n%[^0-9]*c", nome);
    fscanf(arq, "%d", &aposta);

    // verificação da consistencia em relação a aposta
    erroAssert((aposta % 50 == 0 && aposta > 0), "ERRO - a aposta deve ser nao nula e multipla de 50");
}

void leMao(FILE* arq)
{
    // Descricao: Le o naipe e o valor da cartas referentes aos jogadores de entrada do arquivo
    // Entrada: nome do arquivo de entrada
    // Saida: mao[5]

    // variaveis auxiliares para ajudar na leitura da carta
    int valor;
    char naipe;

    // loop criado pare ler um total de 5 cartas
    for (int k = 0; k < 5; k++) {
        fscanf(arq, "%d%c", &valor, &naipe);

        // verificação da consistenciam em relação ao valore e naipe das cartas
        avisoAssert(valor > 0 && valor <= 13, "ERRO - valor de carta invalido");
        avisoAssert((naipe == 'P' || naipe == 'E' || naipe == 'C' || naipe == 'O'), "ERRO - naipe invalido");
        mao[k].setCarta(valor, naipe);
    }
}

int main(int argc, char** argv)
{

    // variaveis auxiliares para determinação da partida
    bool sanidade;
    int quant_rodadas;
    int quant_dinheiro;
    int quant_jogadores;
    int pingo;
    rodadaArranjo rodada;

    // avaliar linha de comando
    parse_args(argc, argv);

    // iniciar registro de acesso
    if (memlog) {
        iniciaMemLog(lognome);
    }

    // ativar ou nao o registro de acesso
    if (regmem) {
        ativaMemLog();
    } else {
        desativaMemLog();
    }

    // abre o arquivo de entrada de dados
    FILE* arq = fopen("entrada.txt", "r");
    // verifica se o arquivo foi devidamente aberto
    erroAssert(arq != NULL, "ERRO - erro ao abrir o arquivo de entrada");

    // abre o arquivo de saida
    FILE* arqw = fopen("saida.txt", "w");
    // verifica se o arquivo foi devidamento aberto
    erroAssert(arqw != NULL, "ERRO - erro ao abrir o arquivo de saida");

    // faz a leitura do dados do arquivo referente ao inicio da partida
    fscanf(arq, "%d %d", &quant_rodadas, &quant_dinheiro);
    // verifica a consistencia dos dados lidos
    erroAssert(quant_rodadas > 0, "ERRO - entre com numero positivo de partidas");
    erroAssert(quant_dinheiro > 0, "ERRO - os jogadores precisam de dinheiro para apostar");

    // loop referente a quantidade de rodadas que acontecerão na partida
    for (int i = 0; i < quant_rodadas; i++) {

        // função que salva os valores necessarios, caso a sanidade seja quebrada e os valores precisem ser resetados
        rodada.Sanidade();

        // faz a leitura dos dados do arquivo referente ao inicio da rodada
        fscanf(arq, "%d %d", &quant_jogadores, &pingo);
        // verifica a consistencia dos dados lidos
        erroAssert(quant_rodadas > 0, "ERRO - entre com numero positivo de jogadores");
        erroAssert(pingo >= 50, "ERRO - o pingo deve ser no minimo 50 unidades de dinheiro");

        // loop referente a quantidae de jogadores em uma partida
        for (int j = 0; j < quant_jogadores; j++) {

            // cenario da primeira rodada, onde todos jogadores participam e precisam ser iniciados na lista de jogadores
            if (i == 0) {
                defineFaseMemLog(0);
                leNomeAposta(arq);
                leMao(arq);
                Jogador novo(nome, quant_dinheiro);
                novo.setMao(mao);
                rodada.InsereInicio(novo);
                sanidade = rodada.SetAposta(novo, aposta);
            }

            // cenario das subsequentes rodadas, onde apena as maos dos jogadores e suas apostas precisam ser atualizadas
            else {
                defineFaseMemLog(1);
                leNomeAposta(arq);
                leMao(arq);
                Jogador novo(nome, quant_dinheiro);
                rodada.SetMao(novo, mao);
                sanidade = rodada.SetAposta(novo, aposta);
            }
        }

        // fim da rodada, onde os vencedores serão decidos e as informações serão salvas no arquivo saida.txt
        defineFaseMemLog(2);
        sanidade = rodada.SetPote(pingo);
        rodada.Pontuacao();
        rodada.Vencedor(arqw, sanidade);
        if (sanidade == true)
            rodada.resetaSanidade();
        rodada.LimpaMao();
        rodada.resetar();
        sanidade = false;
    }

    // finalização da partida, onde os jogadores serão ordenados pela quantidade de dinheiro e as informações serão salvas no arquivo saida.txt
    rodada.ResultadoFinal(arqw);

    // conclui registro de acesso
    if (memlog) {
        finalizaMemLog();
    }
    return 0;
}