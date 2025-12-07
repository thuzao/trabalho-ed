#ifndef BD_TIMES_H
#define BD_TIMES_H

#include "times.h"

typedef struct BD_Partidas BD_Partidas;

//Definição da estrutura do nó da lista encadeada de times
typedef struct TimeNode {
    Times *time;                 // Ponteiro para a estrutura Times
    struct TimeNode *proximo;    // Próximo nó da lista
} TimeNode;

//Estrutura principal que guarda todos os times utilizando lista encadeada
typedef struct BD_Times {
    TimeNode *inicio; //Ponteiro para o primeiro nó da lista (cabeça)
} BD_Times;

//Função para alocar memória para o BD_Times
BD_Times *alocarMemoriaBDTimes();

//Função para liberar memória da lista encadeada de times
void liberarBDTimes(BD_Times *bd);

//Função para adicionar um time na lista encadeada
void adicionarTime(BD_Times *bd, int id, const char *nome);

//Função para carregar os times a partir de um arquivo CSV
void carregarTimes(const char *bd_times, BD_Times *dados);

//Função para buscar um time pelo ID (necessária para TP2)
TimeNode *buscarTimePorID(BD_Times *bd, int id);

//Função para consultar times por prefixo
void consultarTimes(BD_Times *dados);

//Função para imprimir a classificação dos times
void imprimirClassificacao(BD_Times *dados_times);

//Função para atualizar estatísticas dos times de acordo com as partidas
void atualizarDadosTimes(BD_Partidas *dados_das_partidas, BD_Times *dados_dos_times);

//Função para ordernar os times
void ordenarTimes(BD_Times *dados_dos_times);

//Função para comparar dois times
int compararTimes(Times *a, Times *b);

//Função para resetar estatísicas
void resetarEstatisticas(BD_Times *dados_times);

#endif
