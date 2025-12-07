#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "partidas.h"
#include "times.h"
#include "bd_partidas.h"
#include "bd_times.h"

//Forward declaration da função que busca time pelo ID (implementada em bd_times.c)
TimeNode *buscarTimePorID(BD_Times *dados_times, int id);

//Função para criar a partida com suas informações
Partidas *criarPartida(int ID, int t1, int t2, int gst1, int gst2){
    //Alocação de memória para criar a partida
    Partidas *partida = malloc(sizeof(Partidas));
    //Verifica a alocação de espaço da memória
    if (partida == NULL) {
        perror("Erro ao alocar memória para a partida! \n");
        exit(1);
    }
    //Atribui os dados especificos a estrutura partidas
    partida->id = ID;
    partida->time1 = t1;
    partida->time2 = t2;
    partida->gols_time1 = gst1;
    partida->gols_time2 = gst2;
    //Retorna partida
    return partida;
}

//Função para verificar qual time venceu, empatou ou perdeu
int verificarSeFoiEmpate(Partidas *partida){
    if (partida->gols_time1 == partida->gols_time2){
        return 1;
    } else {
        return 0;
    }
}

//Função para atualizar informações do vencedor e do perdedor
void atualizarVencedor(Partidas *partida, Times *time1, Times *time2){
    if (partida->gols_time1 > partida->gols_time2){
        time1->vitorias++;
        time2->derrotas++;
    } else {
        time2->vitorias++;
        time1->derrotas++;
    }
}

//Função para imprimir que a função não foi implementada
void imprimirNaoFoiImplementado(){
    system("clear");
    printf("Esta parte ainda nao foi implementada");
    printf("\n");
}

//Função para verificar o time partidas do time como mandante
int verificarMandante(const char *prefix, Partidas *partida, BD_Times *dados_times){
    int id_mandante = partida->time1;

    //Busca o time mandante na lista encadeada
    TimeNode *node_mandante = buscarTimePorID(dados_times, id_mandante);
    if (node_mandante == NULL) return 0;

    Times *time_mandante = node_mandante->time;

    //Verifica prefixo
    if (verificarPreFixoDoTime(time_mandante->nome_do_time, prefix)){
        return 1;
    } else {
        return 0;
    }
}

//Função para verificar o time partidas do time como visitante
int verificarVisitante(const char *prefix, Partidas *partida, BD_Times *dados_times){
    int id_visitante = partida->time2;

    //Busca o time visitante na lista encadeada
    TimeNode *node_visitante = buscarTimePorID(dados_times, id_visitante);
    if (node_visitante == NULL) return 0;

    Times *time_visitante = node_visitante->time;

    //Verifica prefixo
    if (verificarPreFixoDoTime(time_visitante->nome_do_time, prefix)){
        return 1;
    } else {
        return 0;
    }
}

//Função para imprimir a partida com os dados necessários
void imprimirPartida(Partidas *partida, BD_Times *dados_dos_times){
    //Obtém time mandante
    TimeNode *node_mandante = buscarTimePorID(dados_dos_times, partida->time1);
    Times *t1 = node_mandante->time;

    //Obtém time visitante
    TimeNode *node_visitante = buscarTimePorID(dados_dos_times, partida->time2);
    Times *t2 = node_visitante->time;

    //Imprime as informações da partida
    printf("%d  %s %d x %d  %s \n",
        partida->id,
        t1->nome_do_time, partida->gols_time1,
        partida->gols_time2, t2->nome_do_time
    );
}

