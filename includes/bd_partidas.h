#ifndef BD_PARTIDAS_H
#define BD_PARTIDAS_H

#include "partidas.h"

//Forward declaration  -> Utilizei para evitar a questão de dependência infinita
struct BD_Times;

//Definição da constante de quantidade máxima de partidas
#define PARTIDAS_MAXIMO 4950 //O valor alto é devido a quantidade máxima de times ser 100, com isso, baseado nesse valor, quantidade máxima de partidas é 4950

//Definição da estrutura com um vetor para alocar as partidas
typedef struct BD_Partidas
{
    int qntd;
    Partidas *partidas[PARTIDAS_MAXIMO];
} BD_Partidas;


//Função para alocar a memória do BD_partidas
BD_Partidas *alocarMemoriaBDPartidas();

//Função para liberar memória dos partidas, uma vez que foram alocados dinamicamente
void liberarBDPartidas(BD_Partidas *bd);

//Função para carregar as partidas para o vetor dinâmico. Recebe como parâmetro o nome do arquivo e aonde que será salvo
void carregarPartidas(const char *bd_partidas, BD_Partidas *dados);

//Função que adiciona uma partida ao vetor
void adicionarPartida(BD_Partidas *bd, int id, int time1, int time2, int gols_time1, int gols_time2);

//Função para criar para imprimir o texto para consultar
void imprimirTextoParaConsultarPartidas();

//Função para consultar partidas
void consultarPartidas(BD_Partidas *dados_partidas, BD_Times *dados_times);

//Função que apresenta o menu geral
void imprimirMenuPrincipal();
#endif