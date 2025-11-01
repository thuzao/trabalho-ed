#ifndef BD_PARTIDAS_H
#define BD_PARTIDAS_H

#include "partidas.h"

#define PARTIDAS_MAXIMO 100
typedef struct BD_Partidas
{
    int qntd;
    Partidas *partidas[PARTIDAS_MAXIMO];
} BD_Partidas;

//Função que adiciona uma partida ao vetor
void adicionarPartida(BD_Partidas *bd, int id, int time1, int time2, int gols_time1, int gols_time2);

//Função para alocar a memória dos times
BD_Partidas *alocarMemoriaBDPartidas();

//Função para liberar memória dos times, uma vez que foram alocados dinamicamente
void liberarBDPartidas(BD_Partidas *bd);

#endif