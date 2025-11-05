#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "time.h"
#include "partidas.h"
#include "bd_times.h"
#include "bd_partidas.h"

void carregarPartidas(const char *bd_partidas, BD_Partidas *dados){
    //Lê o arquivo bd_times e armazena na variável
    FILE *arquivo = fopen(bd_partidas, "r");
    
    //Verificação se o arquivo foi lido corretamente
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo %s \n", bd_partidas);
        exit(1);
    };

    //Declarando variáveis para o tamanho máximo de linhas, o id, bem como o nome do time
    char linha[PARTIDAS_MAXIMO];
    int id;
    int time1;
    int time2;
    int gols_time1;
    int gols_time2;

    //Realiza a leitura do cabeçalho, posteriormente, será substituído o valor (Para que possamos ignorar)
    fgets(linha, sizeof(linha), arquivo);
    dados->qntd = 0;

     //Loop para armazenar os valores na estrutura
    while (fgets(linha, sizeof(linha), arquivo)) {
        //A condicional irá pegar o valor do id e o valor do char (Até 99 caracteres ou até achar o \n)
        if (sscanf(linha, "%d, %d, %d, %d, %d", &id, &time1, &time2, &gols_time1, &gols_time2) == 5) {
            adicionarPartida(dados, id, time1, time2, gols_time1, gols_time2);
        }
    }

    //Fechamento da leitura do arquivo
    fclose(arquivo);
}


void adicionarPartida(BD_Partidas *bd, int id, int time1, int time2, int gols_time1, int gols_time2){
    Partidas *partida = criarPartida(id, time1, time2, gols_time1, gols_time2);
    if (bd->qntd >= PARTIDAS_MAXIMO){
        printf("Capacidade máxima de partidas atingida! \n");
        exit(1);
    } else {
        bd->partidas[bd->qntd++] = partida;
    };
}

BD_Partidas *alocarMemoriaBDPartidas(){
    BD_Partidas *bd = malloc(sizeof(BD_Partidas));
    if (bd == NULL) {
        printf("Erro ao alocar memória para estrutura de Partidas\n");
        exit(1);
    }
    return bd;
}

void liberarBDPartidas(BD_Partidas *bd) {
    for (int i = 0; i < bd->qntd; i++) {
        free(bd->partidas[i]);
    }
    free(bd);
}
