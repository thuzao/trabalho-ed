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
void atualizarDadosTimes(BD_Partidas *dados_das_partidas, BD_Times *dados_dos_times){
    for (int i = 0; i < dados_das_partidas->qntd; i++){
        Partidas *partida_verificada = dados_das_partidas->partidas[i];
    
        Times *time1 = dados_dos_times->times[partida_verificada->time1];
        Times *time2 = dados_dos_times->times[partida_verificada->time2];
        //Implementando informações de gols para o time mandante
        adicionarGolsMarcados(time1, partida_verificada->gols_time1);
        adicionarGolsSofridos(time1, partida_verificada->gols_time2);
        
        //Implementando informações de gols para o time visitante
        adicionarGolsMarcados(time2, partida_verificada->gols_time2);
        adicionarGolsSofridos(time2, partida_verificada->gols_time1);
        
        //Verificação se o time venceu, empatou ou perdeu
        if (!verificarSeFoiEmpate(partida_verificada)){
            atualizarVencedor(partida_verificada, time1, time2);
        } else {
            time1->empates++;
            time2->empates++;
        }
    }
}

void atualizarVencedor(Partidas *partida, Times *time1, Times *time2){
    if (partida->gols_time1 > partida->gols_time2){
        time1->vitorias++;
        time2->derrotas++;
    } else {
        time2->vitorias++;
        time1->derrotas++;
    }
}

void consultarTimes(BD_Times *dados){
    char prefixo[TIMES_MAXIMO];
    int times_impressos = 0;
    printf("Digite o nome ou prefixo do time: \n");
    scanf("%s", prefixo); 
    for (int i = 0; i < dados->qntd; i++){
        if (verificarPreFixo(dados->times[i]->nome_do_time, prefixo)){
            imprimirTime(dados->times[i]);
            times_impressos++;
        };
    };
    if (times_impressos == 0){
        printf("Nao foi encontrado nenhum time com este prefixo ou nome \n");
    };
}
