#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "partidas.h"
#include "times.h"
#include "bd_partidas.h"
#include "bd_times.h"

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
    //Verifica se a partida foi empate, comparando a quantidade de gols dos times
    if (partida->gols_time1 == partida->gols_time2){
        return 1; //Foi empate
    } else {
        return 0; //Não foi empate
    }
}

//Função para atualizar informações do vencedor e do perdedor
void atualizarVencedor(Partidas *partida, Times *time1, Times *time2){
    //Verifica se o time 1 fez mais gols, logo, ganhando a partida
    if (partida->gols_time1 > partida->gols_time2){
        time1->vitorias++; //Atribui a vitoria ao time 1
        time2->derrotas++; //Atribui a derrota ao time 2
    } else {
        //Entrando nessa parte, o time 2 obteve a vitoria (fez mais gols que o time 1)
        time2->vitorias++; //Atribui a vitoria ao time 2
        time1->derrotas++; //Atribui a derrota ao time 1
    }
}

//Função para imprimir que a função não foi implementada
void imprimirNaoFoiImplementado(){
    system("clear"); //Limpa o console
    printf("Esta parte ainda nao foi implementada"); //Informa que nao foi implementada
    printf("\n");
}

//Função para verificar o time partidas do time como mandante
int verificarMandante(const char *prefix, Partidas *partida, BD_Times *dados_times){
    int id_mandante = partida->time1; //Obtem o id do time 1, que eh o mandante
    Times *time_mandante = dados_times->times[id_mandante]; //Busca os dados do time 1
    //Verifica o prefixo do time, ou nome e compara com o nome do time, retornando 1 se for
    if (verificarPreFixoDoTime(time_mandante->nome_do_time, prefix)){
        return 1; //Retona que o time é mandante
    } else {
        return 0; //Retorna que o time nao é mandante
    }
}

//Função para verificar o time partidas do time como visitante
int verificarVisitante(const char *prefix, Partidas *partida, BD_Times *dados_times){
    int id_visitante = partida->time2; //Obtem o id do time 2, que eh o visitante
    Times *time_visitante = dados_times->times[id_visitante]; //Busca os dados do time 2
    //Verifica o prefixo do time, ou nome e compara com o nome do time, retornando 1 se for
    if (verificarPreFixoDoTime(time_visitante->nome_do_time, prefix)){
        return 1; //Retorna 1 se for visitante
    } else {
        return 0; //Retorna 0 se não for visitante
    }
}

//Função para imprimir a partida com os dados necessários
void imprimirPartida(Partidas *partida, BD_Times *dados_dos_times){
    //Imprime as informações da partida
    printf("%d  %s %d x %d  %s \n", partida->id, dados_dos_times->times[partida->time1]->nome_do_time, partida->gols_time1,  partida->gols_time2, dados_dos_times->times[partida->time2]->nome_do_time);
}