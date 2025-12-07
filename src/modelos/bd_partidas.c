#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bd_partidas.h"
#include "bd_times.h"
#include "partidas.h"
#include "times.h"

// Forward para buscar time
TimeNode *buscarTimePorID(BD_Times *bd, int id);


// =======================================================
//        ALOCAÇÃO / LIBERAÇÃO
// =======================================================

BD_Partidas *alocarMemoriaBDPartidas() {
    BD_Partidas *bd = malloc(sizeof(BD_Partidas));
    if (!bd) {
        printf("Erro ao alocar memoria para BD_Partidas\n");
        exit(1);
    }
    bd->inicio = NULL;
    return bd;
}

void liberarBDPartidas(BD_Partidas *bd) {
    PartidaNode *aux = bd->inicio;
    while (aux) {
        PartidaNode *tmp = aux->proximo;
        free(aux);
        aux = tmp;
    }
    free(bd);
}


// =======================================================
//        CARREGAR CSV
// =======================================================

void carregarPartidas(const char *arquivo, BD_Partidas *dados) {
    FILE *arq = fopen(arquivo, "r");
    if (!arq) {
        printf("Erro ao abrir arquivo %s\n", arquivo);
        exit(1);
    }

    char linha[200];
    int id, t1, t2, g1, g2;

    fgets(linha, sizeof(linha), arq); // cabeçalho

    while (fgets(linha, sizeof(linha), arq)) {
        if (sscanf(linha, "%d,%d,%d,%d,%d", &id, &t1, &t2, &g1, &g2) == 5)
            adicionarPartida(dados, id, t1, t2, g1, g2);
    }

    fclose(arq);
}


// =======================================================
//        ADICIONAR PARTIDA
// =======================================================

void adicionarPartida(BD_Partidas *bd, int id, int time1, int time2, int gols1, int gols2) {
    Partidas p = *criarPartida(id, time1, time2, gols1, gols2);

    PartidaNode *novo = malloc(sizeof(PartidaNode));
    if (!novo) {
        printf("Erro ao alocar memoria para PartidaNode\n");
        exit(1);
    }

    novo->partida = p;
    novo->proximo = bd->inicio;
    bd->inicio = novo;
}


// =======================================================
//        BUSCAR PARTIDA POR ID
// =======================================================

PartidaNode *buscarPartidaPorID(BD_Partidas *bd, int id) {
    PartidaNode *aux = bd->inicio;
    while (aux) {
        if (aux->partida.id == id)
            return aux;
        aux = aux->proximo;
    }
    return NULL;
}


// =======================================================
//        CONSULTA DE PARTIDAS (MENU COMPLETO DO TP)
// =======================================================

void consultarPartidas(BD_Partidas *dados_partidas, BD_Times *dados_times) {

    int opcao;
    char nome_busca[50];

    while (1) {

        system("clear");

        printf("=========================================\n");
        printf("        CONSULTA DE PARTIDAS\n");
        printf("=========================================\n");
        printf("1 - Buscar por time MANDANTE\n");
        printf("2 - Buscar por time VISITANTE\n");
        printf("3 - Buscar por MANDANTE ou VISITANTE\n");
        printf("4 - Retornar ao menu principal\n");
        printf("=========================================\n");
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);

        if (opcao == 4) return;

        printf("Digite o nome ou prefixo: ");
        scanf("%s", nome_busca);

        int total = 0;
        PartidaNode *aux = dados_partidas->inicio;

        system("clear");
        printf("ID   Time1              Time2              Pl1 Pl2\n");
        printf("----------------------------------------------------\n");

        while (aux) {

            Partidas *p = &aux->partida;
            TimeNode *t1 = buscarTimePorID(dados_times, p->time1);
            TimeNode *t2 = buscarTimePorID(dados_times, p->time2);

            char *nome1 = t1->time->nome_do_time;
            char *nome2 = t2->time->nome_do_time;

            int encontrou = 0;

            switch (opcao) {
                case 1:
                    encontrou = strncmp(nome1, nome_busca, strlen(nome_busca)) == 0;
                    break;
                case 2:
                    encontrou = strncmp(nome2, nome_busca, strlen(nome_busca)) == 0;
                    break;
                case 3:
                    encontrou =
                        strncmp(nome1, nome_busca, strlen(nome_busca)) == 0 ||
                        strncmp(nome2, nome_busca, strlen(nome_busca)) == 0;
                    break;
            }

            if (encontrou) {
                printf("%-4d %-18s %-18s %3d %3d\n",
                       p->id, nome1, nome2, p->gols_time1, p->gols_time2);
                total++;
            }

            aux = aux->proximo;
        }
        
        if (total == 0) {
            printf("\nNenhuma partida encontrada.\n");
        } else {
            return;
        }

        printf("\nPressione ENTER para continuar...");
        getchar(); getchar();
    }
}


// =======================================================
//        GERAR NOVO ID
// =======================================================

int gerarNovoID(BD_Partidas *dados_partidas) {
    int maior = -1;
    PartidaNode *aux = dados_partidas->inicio;

    while (aux) {
        if (aux->partida.id > maior)
            maior = aux->partida.id;
        aux = aux->proximo;
    }
    return maior + 1;
}


// =======================================================
//        INSERIR PARTIDA (FLUXO COMPLETO TP)
// =======================================================

void inserirPartida(BD_Partidas *dados_partidas, BD_Times *dados_times) {

    system("clear");
    printf("INSERIR PARTIDA\n\n");

    int time1, time2, g1, g2;

    printf("Digite o ID do Time1: ");
    scanf("%d", &time1);

    if (!buscarTimePorID(dados_times, time1)) {
        printf("Time1 inexistente.\n");
        return;
    }

    printf("Digite o ID do Time2: ");
    scanf("%d", &time2);

    if (!buscarTimePorID(dados_times, time2)) {
        printf("Time2 inexistente.\n");
        return;
    }

    if (time1 == time2) {
        printf("Os times nao podem ser iguais.\n");
        return;
    }

    printf("Gols Time1: ");
    scanf("%d", &g1);

    printf("Gols Time2: ");
    scanf("%d", &g2);

    int novo_id = gerarNovoID(dados_partidas);

    system("clear");
    printf("Confirma os dados abaixo? (S/N)\n");

    TimeNode *t1 = buscarTimePorID(dados_times, time1);
    TimeNode *t2 = buscarTimePorID(dados_times, time2);

    printf("ID: %d\n", novo_id);
    printf("%s %d x %d %s\n", t1->time->nome_do_time, g1, g2, t2->time->nome_do_time);

    char c;
    scanf(" %c", &c);

    if (c != 'S' && c != 's') {
        printf("Operacao cancelada.\n");
        return;
    }

    adicionarPartida(dados_partidas, novo_id, time1, time2, g1, g2);

    resetarEstatisticas(dados_times);
    atualizarDadosTimes(dados_partidas, dados_times);

    printf("Partida inserida com sucesso!\n");
}


// =======================================================
//        REMOVER PARTIDA
// =======================================================

void removerPartida(BD_Partidas *dados_partidas, BD_Times *dados_times) {

    consultarPartidas(dados_partidas, dados_times);

    int id;
    printf("Digite o ID da partida que deseja remover: ");
    scanf("%d", &id);

    PartidaNode *node = buscarPartidaPorID(dados_partidas, id);

    if (!node) {
        printf("Partida nao encontrada.\n");
        return;
    }

    system("clear");

    printf("Tem certeza que deseja excluir o registro abaixo? (S/N)\n");
    imprimirPartida(&node->partida, dados_times);

    char c;
    scanf(" %c", &c);

    if (c != 'S' && c != 's') {
        printf("Operacao cancelada.\n");
        return;
    }

    PartidaNode *aux = dados_partidas->inicio;
    PartidaNode *ant = NULL;

    while (aux) {
        if (aux->partida.id == id) {
            if (!ant) dados_partidas->inicio = aux->proximo;
            else      ant->proximo = aux->proximo;

            free(aux);
            break;
        }
        ant = aux;
        aux = aux->proximo;
    }

    resetarEstatisticas(dados_times);
    atualizarDadosTimes(dados_partidas, dados_times);

    printf("Partida removida com sucesso!\n");
}


// =======================================================
//        ATUALIZAR PARTIDA (FLUXO COMPLETO TP)
// =======================================================

void atualizarPartida(BD_Partidas *dados_partidas, BD_Times *dados_times) {

    consultarPartidas(dados_partidas, dados_times);

    int id;
    printf("Digite o ID da partida a atualizar: ");
    scanf("%d", &id);

    PartidaNode *node = buscarPartidaPorID(dados_partidas, id);

    if (!node) {
        printf("Partida nao encontrada.\n");
        return;
    }

    Partidas *p = &node->partida;

    char e1[10], e2[10];
    printf("Placar1 atual: %d | Novo (ou -): ", p->gols_time1);
    scanf("%s", e1);

    printf("Placar2 atual: %d | Novo (ou -): ", p->gols_time2);
    scanf("%s", e2);

    int novo1 = (e1[0] == '-') ? p->gols_time1 : atoi(e1);
    int novo2 = (e2[0] == '-') ? p->gols_time2 : atoi(e2);

    // Preview
    TimeNode *t1 = buscarTimePorID(dados_times, p->time1);
    TimeNode *t2 = buscarTimePorID(dados_times, p->time2);

    printf("Confirmar? (S/N)\n");
    printf("ID %d | %s %d x %d %s\n",
           p->id, t1->time->nome_do_time, novo1, novo2, t2->time->nome_do_time);

    char c;
    scanf(" %c", &c);

    if (c != 'S' && c != 's') {
        printf("Operacao cancelada.\n");
        return;
    }

    p->gols_time1 = novo1;
    p->gols_time2 = novo2;

    resetarEstatisticas(dados_times);
    atualizarDadosTimes(dados_partidas, dados_times);

    printf("Registro atualizado com sucesso!\n");
}


// =======================================================
//        SALVAR CSV
// =======================================================

void salvarPartidasCSV(const char *arquivo, BD_Partidas *dados) {

    FILE *arq = fopen(arquivo, "w");
    if (!arq) {
        printf("Erro ao abrir %s\n", arquivo);
        exit(1);
    }

    fprintf(arq, "ID,Time1,Time2,Gols1,Gols2\n");

    PartidaNode *aux = dados->inicio;

    while (aux) {
        Partidas *p = &aux->partida;
        fprintf(arq, "%d,%d,%d,%d,%d\n",
                p->id, p->time1, p->time2, p->gols_time1, p->gols_time2);
        aux = aux->proximo;
    }

    fclose(arq);
}
