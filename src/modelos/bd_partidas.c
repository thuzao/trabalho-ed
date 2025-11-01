#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leitura.h"

void adicionarPartida(BD_Partidas *bd, int id, int time1, int time2, int gols_time1, int gols_time2){
    Partidas *partida = criarPartida(id, time1, time2, gols_time1, gols_time2);
    if (bd->qntd >= PARTIDAS_MAXIMO){
        printf("Capacidade máxima de partidas atingida! \n");
        exit(1);
    } else {
        bd->partidas[bd->qntd++] = partida;
    };
}

BD_Partidas *alocarMemoriaBDPartidas(){
    BD_Partidas *bd = malloc(sizeof(BD_Partidas));
    if (bd == NULL) {
        printf("Erro ao alocar memória para estrutura de Partidas\n");
        exit(1);
    }
    return bd;
}

void liberarBDPartidas(BD_Partidas *bd) {
    for (int i = 0; i < bd->qntd; i++) {
        free(bd->partidas[i]);
    }
    free(bd);
}
