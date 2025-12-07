#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bd_times.h"
#include "times.h"
#include "bd_partidas.h"

//Função para alocar memória para estrutura BD_Times
BD_Times *alocarMemoriaBDTimes() {

    BD_Times *bd = malloc(sizeof(BD_Times));

    if (bd == NULL) {
        printf("Erro ao alocar memoria para estrutura de Times\n");
        exit(1);
    }

    //Inicializa a cabeça da lista
    bd->inicio = NULL;

    return bd;
}

//Função para liberar memória da lista encadeada de times
void liberarBDTimes(BD_Times *bd) {

    TimeNode *aux = bd->inicio;

    //Percorre toda a lista e libera memória individualmente
    while (aux != NULL) {
        TimeNode *temp = aux->proximo;
        free(aux->time);     //libera o struct Times
        free(aux);           //libera o nó
        aux = temp;
    }

    free(bd);
}

//Função para adicionar time à lista encadeada
void adicionarTime(BD_Times *bd, int id, const char *nome) {

    //Cria o time utilizando a função já existente
    Times *time = criarTime(id, nome);

    //Cria novo nó da lista
    TimeNode *novo = malloc(sizeof(TimeNode));

    if (novo == NULL) {
        printf("Erro ao alocar memoria para novo TimeNode\n");
        exit(1);
    }

    novo->time = time;
    novo->proximo = bd->inicio;

    //Insere no início da lista
    bd->inicio = novo;
}

//Função para carregar times a partir do CSV
void carregarTimes(const char *bd_times, BD_Times *dados){

    FILE *arquivo = fopen(bd_times, "r");

    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo %s\n", bd_times);
        exit(1);
    }

    char linha[200];
    int id;
    char nome[TAMANHO_NOME_TIME];

    //Ignora cabeçalho
    fgets(linha, sizeof(linha), arquivo);

    //Lê linha a linha
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (sscanf(linha, "%d,%29[^\n]", &id, nome) == 2) {
            adicionarTime(dados, id, nome);
        }
    }

    fclose(arquivo);
}

//Função para buscar um time pelo ID na lista encadeada
TimeNode *buscarTimePorID(BD_Times *bd, int id){

    TimeNode *aux = bd->inicio;

    //Percorre a lista procurando o ID
    while (aux != NULL) {
        if (aux->time->ID == id)
            return aux;

        aux = aux->proximo;
    }

    //Caso não encontre
    return NULL;
}

//Função para imprimir a classificação
void imprimirClassificacao(BD_Times *dados_times){
    char encerramento;

    system("clear");
    imprimirCabecalhoDeDadosDosTimes();

    TimeNode *aux = dados_times->inicio;

    //Percorre lista e imprime
    while (aux != NULL) {
        imprimirTime(aux->time);
        aux = aux->proximo;
    }

    printf("\n\nDigite qualquer tecla para voltar ao menu principal: ");
    scanf("%s", &encerramento);
    system("clear");
}

//Função para consultar time baseado no prefixo
void consultarTimes(BD_Times *dados){
    char encerramento;
    char prefixo[50];
    int times_impressos = 0;

    system("clear");

    printf("Digite o nome ou prefixo do time: ");
    scanf("%s", prefixo);
    printf("\n");

    TimeNode *aux = dados->inicio;

    while (aux != NULL) {
        if (verificarPreFixoDoTime(aux->time->nome_do_time, prefixo)) {
            if (times_impressos == 0)
                imprimirCabecalhoDeDadosDosTimes();

            imprimirTime(aux->time);
            times_impressos++;
        }

        aux = aux->proximo;
    }

    if (times_impressos == 0) {
        printf("Nao foi encontrado nenhum time com este prefixo ou nome\n");
    }

    printf("\n\nDigite qualquer tecla para voltar ao menu principal: ");
    scanf("%s", &encerramento);
    system("clear");
}

//Função para atualizar estatísticas dos times após as partidas
void atualizarDadosTimes(BD_Partidas *dados_das_partidas, BD_Times *dados_dos_times){

    PartidaNode *aux = dados_das_partidas->inicio;

    while (aux != NULL){

        Partidas *p = &(aux->partida);

        TimeNode *t1_node = buscarTimePorID(dados_dos_times, p->time1);
        TimeNode *t2_node = buscarTimePorID(dados_dos_times, p->time2);

        Times *time1 = t1_node->time;
        Times *time2 = t2_node->time;

        adicionarGolsMarcados(time1, p->gols_time1);
        adicionarGolsSofridos(time1, p->gols_time2);

        adicionarGolsMarcados(time2, p->gols_time2);
        adicionarGolsSofridos(time2, p->gols_time1);

        if (!verificarSeFoiEmpate(p)){
            atualizarVencedor(p, time1, time2);
        } else {
            time1->empates++;
            time2->empates++;
        }

        calcularPontuacao(time1);
        calcularPontuacao(time2);

        aux = aux->proximo;
    }
    ordenarTimes(dados_dos_times);
}

int compararTimes(Times *time1, Times *time2){

    // 1) Pontuação (ordem decrescente)
    if (time1->pontuacao != time2->pontuacao)
        return time2->pontuacao - time1->pontuacao;

    // 2) Vitórias (ordem decrescente)
    if (time1->vitorias != time2->vitorias)
        return time2->vitorias - time1->vitorias;

    // 3) Saldo de gols (ordem decrescente)
    if (time1->saldo_de_gols != time2->saldo_de_gols)
        return time2->saldo_de_gols - time1->saldo_de_gols;

    // Empate total
    return 0;
}

void ordenarTimes(BD_Times *dados_dos_times){

    // Lista vazia
    if (!dados_dos_times->inicio) 
        return;

    int trocou;

    do {
        trocou = 0;
        TimeNode *atual = dados_dos_times->inicio;

        // Varre a lista comparando pares consecutivos
        while (atual->proximo != NULL){

            // Se estiver fora de ordem → troca
            if (compararTimes(atual->time, atual->proximo->time) > 0){

                Times *tmp = atual->time;
                atual->time = atual->proximo->time;
                atual->proximo->time = tmp;

                trocou = 1;
            }

            atual = atual->proximo;
        }

    } while (trocou);
}
//Função para resetar todas as estatísticas dos times
void resetarEstatisticas(BD_Times *dados_times){

    TimeNode *aux = dados_times->inicio;

    while (aux != NULL){
        Times *t = aux->time;

        t->vitorias = 0;
        t->empates = 0;
        t->derrotas = 0;
        t->gols_marcados = 0;
        t->gols_sofridos = 0;
        t->saldo_de_gols = 0;
        t->pontuacao = 0;

        aux = aux->proximo;
    }
}   

