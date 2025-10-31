#ifndef LEITURA_H
#define LEITURA_H


#include "./modelos/bd_times.h"
#include "./modelos/bd_partidas.h"

//Função para carregar os times para o vetor dinâmico. Recebe como parâmetro o nome do arquivo e aonde que será salvo
void carregarTimes(const char *bd_times, BD_Times *dados);

//Função para carregar as partidas para o vetor dinâmico. Recebe como parâmetro o nome do arquivo e aonde que será salvo
void carregarPartidas(const char *bd_partidas, BD_Partidas *dados);

#endif