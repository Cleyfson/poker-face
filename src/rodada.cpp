#include "rodada.hpp"
#include "memlog.hpp"
#include "msgassert.hpp"

void rodadaArranjo::InsereInicio(Jogador jogador)
// Descricao: Insere jogador na rodada
// Entrada: jogador
// Saida: lista com um jogador a mais
{
    if (tamanho == MAXTAM)
        throw "ERRO: rodada cheia!";
    tamanho++;
    for (int i = tamanho; i > 0; i--) {
        jogadores[i] = jogadores[i - 1];
        LEMEMLOG((long int)(&(jogadores[i])), sizeof(Jogador), 0);
        ESCREVEMEMLOG((long int)(&(jogadores[i])), sizeof(Jogador), 0);
    }
    jogadores[0] = jogador;
};

Jogador rodadaArranjo::RemoveInicio()
// Descricao: remove um jogador da rodada
// Entrada: nao tem
// Saida: lista com um jogador a menos
{
    Jogador aux;
    if (tamanho == 0)
        throw "ERRO: rodada vazia!";
    aux = jogadores[0];
    for (int i = 0; i < tamanho; i++) {
        jogadores[i] = jogadores[i + 1];
        LEMEMLOG((long int)(&(jogadores[i])), sizeof(Jogador), 0);
        ESCREVEMEMLOG((long int)(&(jogadores[i])), sizeof(Jogador), 0);
    }
    tamanho--;
    return aux;
};

void rodadaArranjo::Imprime()
// Descricao: imprime dados sobre os jogadores participando da partida
// Entrada: nao tem
// Saida:  impressao na saida padrao (stdout)
{
    int i;
    for (i = 0; i < tamanho; i++) {
        jogadores[i].imprime();
        LEMEMLOG((long int)(&(jogadores[i])), sizeof(Jogador), 0);
    }
    printf("\n");
};

void rodadaArranjo::Sanidade()
// Descricao: itera pela lista de jogadores, salvando o estado monetario dos jogadores
// Entrada: nao tem
// Saida: vetor dinheiro_old preenchido
{
    for (int i = 0; i < tamanho; i++) {
        dinheiro_old[i] = jogadores[i].getDinheiro();
        LEMEMLOG((long int)(&(jogadores[i])), sizeof(Jogador), 0);
    }
}

void rodadaArranjo::resetaSanidade()
// Descricao: itera pela lista de jogadores, restaurando estado monetario
// Entrada: nao tem
// Saida: jogadores com dinheiro no estado pre-aposta/pre-rodada
{
    for (int i = 0; i < tamanho; i++) {
        jogadores[i].resetaDinheiro(dinheiro_old[i]);
        ESCREVEMEMLOG((long int)(&(jogadores[i])), sizeof(Jogador), 0);
    }
}

void rodadaArranjo::Pontuacao()
// Descricao: itera pela lista de jogadores, testando sua pontuação
// Entrada: nao tem
// Saida: atributo pontos dos jogadores devidamente ranqueado
{
    for (int i = 0; i < tamanho; i++) {
        jogadores[i].pontuacao();
        LEMEMLOG((long int)(&(jogadores[i])), sizeof(Jogador), 0);
    }
};

void rodadaArranjo::SetMao(Jogador novo, Carta mao[])
// Descricao: itera pela lista de jogadores, caso confirmado o nome, sua mão de cartas sera atualizada
// Entrada: Jogador, Mao
// Saida: jogador com um novo set de mao
{
    int aux = 0;
    for (int i = 0; i < tamanho; i++) {
        if (jogadores[i].getNome() == novo.getNome()) {
            jogadores[i].setMao(mao);
            ESCREVEMEMLOG((long int)(&(jogadores[i])), sizeof(Jogador), 0);
            aux++;
        }
    }

    // checa se o apostando está listado na primeira rodada
    erroAssert(aux != 0, "nome do jogador não encontrado, na lista inicial de participantes");
};

bool rodadaArranjo::SetPote(int pote)
// Descricao: itera pela lista de jogadores, retirando de seu saldo monetario, o valor referente ao pingo
// Entrada: pote
// Saida: dinheiro dos jogadores decrescido do valor do pote, sanidade
{
    bool sanidade = false;
    for (int i = 0; i < tamanho; i++) {

        // teste a sanidade está ativa
        if (sanidade == false)
            sanidade = jogadores[i].setPote(pote);
        else
            jogadores[i].setPote(pote);
        LEMEMLOG((long int)(&(jogadores[i])), sizeof(Jogador), 0);
    }

    // adiciona ao valor do montante da rodada, o valor da soma do pingo de todos jogadores
    montante += (pote * tamanho);
    return sanidade;
};

bool rodadaArranjo::SetAposta(Jogador novo, int aposta)
// Descricao: itera pela lista de jogadores, caso o nome seja confirmado, aposta sera realizada, e o valor decrescido do total do jogador
// Entrada: Jogador, aposta
// Saida: dinheiro dos jogadores decrescido do valor da aposta, sanidade
{
    bool sanidade = false;
    for (int i = 0; i < tamanho; i++) {
        if (jogadores[i].getNome() == novo.getNome()) {
            if (sanidade == false)
                sanidade = jogadores[i].setAposta(aposta);
            else
                jogadores[i].setAposta(aposta);
            LEMEMLOG((long int)(&(jogadores[i])), sizeof(Jogador), 0);
        }
    }
    montante += aposta;
    return sanidade;
};

void rodadaArranjo::Vencedor(FILE* arqw, bool sanidade)
// Descricao: ajusta os detalhes finais da rodada e registra no arquivo saida.txt
// Entrada: arqw, sanidade
// Saida: saida.txt devidamente preenchido
{

    // testa se a sanidade está ativa, caso sim, registra partida invalida no arquivo saida.txt
    if (sanidade == true) {
        fprintf(arqw, "%d %d %s\n", 0, 0, "I");
        return;
    }

    // inicia variaveis auxiliares
    int max = 0;
    int vencedores = 0;
    std::string nomes;
    std::string mao;

    // itera pela lista de jogadores, procurando pela pontuação maxima
    for (int i = 0; i < tamanho; i++) {
        if (jogadores[i].getPontos() > max) {
            max = jogadores[i].getPontos();
            LEMEMLOG((long int)(&(jogadores[i])), sizeof(Jogador), 0);
        }
    }

    // itera novamente pela lista de jogadores, salvando nas variveis os nomes e mão dos jogador(es) com pontuação maxima
    for (int i = 0; i < tamanho; i++) {
        if (jogadores[i].getPontos() == max) {
            nomes += jogadores[i].getNome();
            nomes += "\n";
            mao = jogadores[i].getMao();
            vencedores++;
        }
        LEMEMLOG((long int)(&(jogadores[i])), sizeof(Jogador), 0);
    }

    // itera uma ultima vez pela lista de jogadores, contemplando aos vencedores (com pontuação maxima), o valor do montante
    for (int i = 0; i < tamanho; i++) {
        if (jogadores[i].getPontos() == max) {
            jogadores[i].setDinheiro(montante / vencedores);
        }
        LEMEMLOG((long int)(&(jogadores[i])), sizeof(Jogador), 0);
    }

    // registra no arquivo saida.txt o nome e mao dos jogadores vencedores (com pontuação maxima)
    fprintf(arqw, "%d %d %s\n", vencedores, montante / vencedores, mao.c_str());
    fprintf(arqw, "%s", nomes.c_str());
};

void Insercao(Jogador v[], int n)
// Descricao: ordena a lista de jogadores, por ordem de quantidade de dinheiro
// Entrada: Jogador v[], n
// Saida: vetor de jogador, devidamente ordenados
{
    int i, j;
    Jogador aux;
    for (i = 1; i < n; i++) {
        aux = v[i];
        j = i - 1;
        while ((j >= 0) && (aux.getDinheiro() > v[j].getDinheiro())) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = aux;
    }
}

void rodadaArranjo::ResultadoFinal(FILE* arqw)
// Descricao: registra os detalhes finais da partida no arquivo saida.txt
// Entrada: arqw
// Saida: saida.txt devidamente preenchido
{
    Insercao(jogadores, tamanho);
    fprintf(arqw, "####\n");
    for (int i = 0; i < tamanho; i++) {
        fprintf(arqw, "%s %d\n", jogadores[i].getNome().c_str(), jogadores[i].getDinheiro());
        LEMEMLOG((long int)(&(jogadores[i])), sizeof(Jogador), 0);
        ESCREVEMEMLOG((long int)(&(jogadores[i])), sizeof(Jogador), 0);
    }
};

void rodadaArranjo::LimpaMao()
// Descricao: itera pela lista de jogadores, limpando suas mao de cartas
// Entrada: nao tem
// Saida: mao dos jogadores com valor = 0 e naipe = '-'
{
    for (int i = 0; i < tamanho; i++) {
        jogadores[i].limpaMao();
        ESCREVEMEMLOG((long int)(&(jogadores[i])), sizeof(Jogador), 0);
    }
};

void rodadaArranjo::resetar()
// Descricao: itera pela lista de jogadores, zerando suas pontuacoes e zera o montantes
// Entrada: nao tem
// Saida: jogadores com pontos = 0, montante = 0
{
    montante = 0;
    for (int i = 0; i < tamanho; i++) {
        jogadores[i].zerarPontos();
        ESCREVEMEMLOG((long int)(&(jogadores[i])), sizeof(Jogador), 0);
    }
};

void rodadaArranjo::Limpa()
// Descricao: limpa a lista de jogadores
// Entrada: nao tem
// Saida: tamanho da lista = 0
{
    tamanho = 0;
};