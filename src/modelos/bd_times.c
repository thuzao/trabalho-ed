#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "time.h"
#include "partidas.h"
#include "bd_partidas.h"
#include "bd_times.h"

void carregarTimes(const char *bd_times, BD_Times *dados){
    //Lê o arquivo bd_times e armazena na variável
    FILE *arquivo = fopen(bd_times, "r");
    
    //Verificação se o arquivo foi lido corretamente
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo %s \n", bd_times);
        exit(1);
    };

    //Declarando variáveis para o tamanho máximo de linhas, o id, bem como o nome do time
    char linha[TIMES_MAXIMO];
    int id;
    char nome[TAMANHO_NOME_TIME];

    //Realiza a leitura do cabeçalho, posteriormente, será substituído o valor (Para que possamos ignorar)
    fgets(linha, sizeof(linha), arquivo);
    dados->qntd = 0;

    //Loop para armazenar os valores na estrutura
    while (fgets(linha, sizeof(linha), arquivo)) {
        //A condicional irá pegar o valor do id e o valor do char (Até 99 caracteres ou até achar o \n)
        if (sscanf(linha, "%d,%99[^\n]", &id, nome) == 2) {
            adicionarTime(dados, id, nome);
        }
    }

    //Fechamento da leitura do arquivo
    fclose(arquivo);
}


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
        calcularPontuacao(time1);
        calcularPontuacao(time2);
    }
}

void imprimirClassificacao(BD_Times *dados_times){
    printf("%-5s %-10s %-5s %-5s %-5s %-5s %-5s %-5s %-5s \n", "ID", "Time", "V", "E", "D", "GM", "GS", "SG", "PG");
    for (int i = 0; i < dados_times->qntd; i++){
        imprimirTime(dados_times->times[i]);
    }
}

void consultarTimes(BD_Times *dados){
    char prefixo[TIMES_MAXIMO];
    int times_impressos = 0;
    printf("Digite o nome ou prefixo do time: \n");
    scanf("%s", prefixo); 
    for (int i = 0; i < dados->qntd; i++){
        if (verificarPreFixoDoTime(dados->times[i]->nome_do_time, prefixo)){
            imprimirTime(dados->times[i]);
            times_impressos++;
        };
    };
    if (times_impressos == 0){
        printf("Nao foi encontrado nenhum time com este prefixo ou nome \n");
    };
}
