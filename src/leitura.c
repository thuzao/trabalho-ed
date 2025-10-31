#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leitura.h"

#include "../includes/modelos/bd_times.h"
#include "../includes/modelos/bd_partidas.h"

void carregarTimes(const char bd_times, BD_Times *dados){
    FILE *arquivo = fopen(bd_times, "r");
    
    //Verificação se o arquivo foi lido corretamente
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo %s \n", bd_times);
    } else {

        
    }

}