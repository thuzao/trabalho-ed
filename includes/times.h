#ifndef TIMES_H
#define TIMES_H

//Definição da constante de tamanho do nome máximo do time
#define TAMANHO_NOME_TIME 30

//Definição da estrutura times
typedef struct 
{
    int ID;
    char nome_do_time[TAMANHO_NOME_TIME];
    int vitorias;
    int empates;
    int derrotas;
    int gols_marcados;
    int gols_sofridos;
    int pontuacao;
    int saldo_de_gols;
} Times;


//Função para criar time
Times *criarTime(int id, const char *nome);

//Função para imprimir o time e as suas informações
void imprimirTime(Times *time);

//Função para imprimir cabeçalho de para informações do time (ID, NOME, VITÓRIAS e etc)
void imprimirCabecalhoDeDadosDosTimes();

//Função que retorna a pontuação do time
int pontuacaoTime(Times *time, int id);

//Função que retorna o saldo de gols
int saldoDeGols(Times *time, int id);

//Função que, dado um prefixo, verifica se o time possui o mesmo.
int verificarPreFixoDoTime(const char *nome_do_time, const char *prefixo);

//Função que calcular a pontuação dos time
void calcularPontuacao(Times *time);

//Função para adicionar os gols marcados
void adicionarGolsMarcados(Times *time, int gols);

//Função para adicionar os gols sofridos
void adicionarGolsSofridos(Times *time, int gols);

#endif