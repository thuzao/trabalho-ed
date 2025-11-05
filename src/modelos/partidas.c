#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "partidas.h"


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

void imprimirPartida(Partidas *partida){
    printf("%d, %d, %d, %d, %d \n", partida->id, partida->time1, partida->time2, partida->gols_time1, partida->gols_time2);
}