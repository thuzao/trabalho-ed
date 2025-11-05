#ifndef PARTIDAS_H
#define PARTIDAS_H

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

//Função para imprimir a partida com os dados necessários
void imprimirPartida(Partidas *partida);

#endif