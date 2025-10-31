#ifndef BD_TIMES_H
#define BD_TIMES_H

#include "times.h"

#define TIMES_MAXIMO 100
typedef struct 
{
    Times *times[TIMES_MAXIMO];
    int qntd;

} BD_Times;

//Função que adiciona um time ao vetor
void adicionarTime(BD_Times *bd, int id, const char *nome_do_time);

//Função que verificar se já existe time
int existeTime(BD_Times *bd, char *nome_do_time);


//Função para liberar memória dos times, uma vez que foram alocados dinamicamente
void liberarBDTimes(BD_Times *bd);



#endif