#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "times.h"

//Função para criar time
Times *criarTime(int id, const char *nome){
    //Realiza a alocação de memória para o time criado
    Times *time = malloc(sizeof(Times));
    
    //Verifica se a alocação de memória foi correta
    if (time == NULL) {
        perror("Erro ao alocar memória para Time! \n");
        exit(1);
    }

    //Declarando ID do time
    time->ID = id;
    
    //Declarando nome do time - Copiando nome do time para o char da estrutura
    strncpy(time->nome_do_time, nome, TAMANHO_NOME_TIME - 1);
    time->nome_do_time[TAMANHO_NOME_TIME - 1] = '\0'; //Garantir o \0 no final do char
    
    //Declaração de estatísticas do time
    time->vitorias = 0;
    time->empates = 0;
    time->derrotas = 0;
    time->gols_marcados = 0;
    time->gols_sofridos = 0;

    return time;
}

//Função para imprimir o time e as suas informações
void imprimirTime(Times *time){
    //Realiza a impressão dos dados de um time
    printf("%-5d %-10s %-5d %-5d %-5d %-5d %-5d %-5d %-5d \n", time->ID, time->nome_do_time, time->vitorias, time->empates, time->derrotas, time->gols_marcados, time->gols_sofridos, time->saldo_de_gols, time->pontuacao);
}

//Função para imprimir cabeçalho de para informações do time (ID, NOME, VITÓRIAS e etc)
void imprimirCabecalhoDeDadosDosTimes(){
    printf("%-5s %-10s %-5s %-5s %-5s %-5s %-5s %-5s %-5s \n", "ID", "Time", "V", "E", "D", "GM", "GS", "SG", "PG");
}

//Função que, dado um prefixo, verifica se o time possui o mesmo.
int verificarPreFixoDoTime(const char *nome_do_time, const char *prefixo){

    //Verificacao para ver se prefixo ou nome do time está vazio, evitando erros.
    if (nome_do_time == NULL || prefixo == NULL) return 0;

    //Looping para verificar o prefixo, enquanto o prefixo não for nulo (\0)
    while (*prefixo) {
        //o loopping irá verificar se elemento verificado no nome_do_time é igual ao elemento do prefixo
        if (*prefixo++ != *nome_do_time++)
            //Retorna zero se o elemento for diferente, encerrando a execução da função
            return 0;
    }
    //Retorna ao sair do looping, aprovando o prefixo igual ao inicio do nome do time
    return 1;
}

//Função que calcular a pontuação dos time
void calcularPontuacao(Times *time){
    time->pontuacao = ((time->vitorias * 3) + (time->empates)); //Atribui a pontuaçãa ao atributo pontuação no struct times
    time->saldo_de_gols = (time->gols_marcados - time->gols_sofridos); //Atribui o saldo de gols no struct times
}

//Função que adicionar os gols marcados as estatísticas do time
void adicionarGolsMarcados(Times *time, int gols){
    time->gols_marcados += gols; //Atribui gols marcados ao time especifico
}

//Função que adicionar os gols sofridos as estatísticas do time
void adicionarGolsSofridos(Times *time, int gols){
    time->gols_sofridos += gols; //Atribui gols sofridos a estatistica do time
}