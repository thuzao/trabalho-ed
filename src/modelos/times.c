#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "times.h"

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
    time->nome_do_time[TAMANHO_NOME_TIME - 1] = '\0'; //Garantir o \n no final do char
    
    //Declaração de estatísticas do time
    time->vitorias = 0;
    time->empates = 0;
    time->derrotas = 0;
    time->gols_marcados = 0;
    time->gols_sofridos = 0;

    return time;
}

void imprimirTime(Times *time){
    //Realiza a impressão do time
    printf("%d, %s, %d, %d, %d, %d, %d, %d, %d \n", time->ID, time->nome_do_time, time->vitorias, time->empates, time->derrotas, time->gols_marcados, time->gols_sofridos, time->pontuacao, time->saldo_de_gols);
}

int verificarPreFixo(const char *nome_do_time, const char *prefixo){

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

void calcularPontuacao(Times *time){
    time->pontuacao = ((time->vitorias * 3) + (time->empates));
    time->saldo_de_gols = (time->gols_marcados - time->gols_sofridos);
}

//Função que adicionar os gols marcados as estatísticas do time
void adicionarGolsMarcados(Times *time, int gols){
    time->gols_marcados += gols;
}

//Função que adicionar os gols sofridos as estatísticas do time
void adicionarGolsSofridos(Times *time, int gols){
    time->gols_sofridos += gols;
}