#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leitura.h"
#include "time.h"

void adicionarTime(BD_Times *bd, int id, const char *nome_do_time){
    Times *time = criarTime(id, nome_do_time);
    if (bd->qntd >= TIMES_MAXIMO){
        printf("Capacidade máxima de times atingida! \n");
        exit(1);
    } else {
        bd->times[bd->qntd++] = time;
    };
}


BD_Times *alocarMemoriaBDTimes() {
    BD_Times *bd = malloc(sizeof(BD_Times));
    if (bd == NULL) {
        printf("Erro ao alocar memória para estrutura de Times\n");
        exit(1);
    }
    return bd;
}

void liberarBDTimes(BD_Times *bd) {
    for (int i = 0; i < bd->qntd; i++) {
        free(bd->times[i]);
    }
    free(bd);
}
