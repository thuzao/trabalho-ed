#ifndef BD_PARTIDAS_H
#define BD_PARTIDAS_H

#include "partidas.h"

struct BD_Times;


#define PARTIDAS_MAXIMO 100
typedef struct BD_Partidas
{
    int qntd;
    Partidas *partidas[PARTIDAS_MAXIMO];
} BD_Partidas;


//Função para carregar as partidas para o vetor dinâmico. Recebe como parâmetro o nome do arquivo e aonde que será salvo
void carregarPartidas(const char *bd_partidas, BD_Partidas *dados);

//Função que adiciona uma partida ao vetor
void adicionarPartida(BD_Partidas *bd, int id, int time1, int time2, int gols_time1, int gols_time2);

//Função para criar para imprimir o texto para consultar
void imprimirTextoParaConsultarPartidas();

//Função para consultar partidas
void consultarPartidas(BD_Partidas *dados);

//Função para alocar a memória dos times
BD_Partidas *alocarMemoriaBDPartidas();

//Função para liberar memória dos times, uma vez que foram alocados dinamicamente
void liberarBDPartidas(BD_Partidas *bd);

#endif