#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "partidas.h"
#include "times.h"
#include "bd_partidas.h"
#include "bd_times.h"

Partidas *criarPartida(int ID, int t1, int t2, int gst1, int gst2){
    Partidas *partida = malloc(sizeof(Partidas));
    if (partida == NULL) {
        perror("Erro ao alocar memória para a partida! \n");
        exit(1);
    }
    partida->id = ID;
    partida->time1 = t1;
    partida->time2 = t2;
    partida->gols_time1 = gst1;
    partida->gols_time2 = gst2;

    return partida;
}

int verificarSeFoiEmpate(Partidas *partida){
    int count = 0;
    if (partida->gols_time1 == partida->gols_time2){
        return 1;
        printf("%d\n", count++);
    } else {
        return 0;
    }
}

void atualizarVencedor(Partidas *partida, Times *time1, Times *time2){
    if (partida->gols_time1 > partida->gols_time2){
        time1->vitorias++;
        time2->derrotas++;
    } else {
        time2->vitorias++;
        time1->derrotas++;
    }
}

int verificarMandante(const char *prefix, Partidas *partida, BD_Times *dados_times){
    int id_mandante = partida->time1;
    Times *time_mandante = dados_times->times[id_mandante];
    if (verificarPreFixoDoTime(time_mandante->nome_do_time, prefix)){
        return 1;
    } else {
        return 0;
    }
}


void imprimirPartida(Partidas *partida, BD_Times *dados_dos_times){
    printf("%d  %s %d x %d  %s \n", partida->id, dados_dos_times->times[partida->time1]->nome_do_time, partida->gols_time1,  partida->gols_time2, dados_dos_times->times[partida->time2]->nome_do_time);
}