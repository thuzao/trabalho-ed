#ifndef TIMES_H
#define TIMES_H

#define TAMANHO_NOME_TIME 30

typedef struct 
{
    int ID;
    char nomeDoTime[TAMANHO_NOME_TIME];
    int vitorias;
    int empates;
    int derrotas;
    int gols_marcados;
    int gols_sofridos;
} Times;


//Função para criar time
Times criarTime(int id, const char *nome);

//Função que retorna a pontuação do time
int pontuacaoTime(Times *time, int id);

//Função que retorna o saldo de gols
int saldoDeGols(Times *time, int id);


#endif