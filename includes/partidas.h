#ifndef PARTIDAS_H
#define PARTIDAS_H

#include "times.h"
#include "bd_times.h"

typedef struct 
{
    int id;
    int time1;
    int time2;
    int gols_time1;
    int gols_time2;
} Partidas;


//Função para criar a partida com suas informações
Partidas *criarPartida(int ID, int t1, int t2, int gst1, int gst2);

//Função para verificar qual time venceu, empatou ou perdeu
int verificarSeFoiEmpate(Partidas *partida);

//Função para atualizar informações do vencedor e do perdedor
void atualizarVencedor(Partidas *partida, Times *time1, Times *time2);

//Função para verificar o time partidas do time como mandante
int verificarMandante(const char *prefix, Partidas *partida, BD_Times *dados_times);

//Função para imprimir a partida com os dados necessários
void imprimirPartida(Partidas *partida, BD_Times *dados_dos_times);

#endif