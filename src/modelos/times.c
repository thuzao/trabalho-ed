#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leitura.h"


Times *criarTime(int id, const char *nome){
    Times *time;
    
    //Declarando ID do time
    time->ID = id;
    
    //Declarando nome do time - Copiando nome do time para o char da estrutura
    strncpy(time->nomeDoTime, nome, TAMANHO_NOME_TIME - 1);
    time->nomeDoTime[TAMANHO_NOME_TIME - 1] = '\0'; //Garantir o \n no final do char
    
    //Declaração de estatísticas do time
    time->vitorias = 0;
    time->empates = 0;
    time->derrotas = 0;
    time->gols_marcados = 0;
    time->gols_sofridos = 0;

    return time;
}