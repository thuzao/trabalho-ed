#ifndef BD_TIMES_H
#define BD_TIMES_H

#include "times.h"

//Forward declaration  -> Utilizei para evitar a questão de dependência infinita
typedef struct BD_Partidas BD_Partidas;

//Definicao da constante de tamanho maximo da quantidade de time
#define TIMES_MAXIMO 100
//Definição da estrutura com um vetor para alocar os times
typedef struct 
{
    Times *times[TIMES_MAXIMO];
    int qntd;

} BD_Times;

//Função para carregar os times para o vetor dinâmico. Recebe como parâmetro o nome do arquivo e aonde que será salvo
void carregarTimes(const char *bd_times, BD_Times *dados);

//Função que adiciona um time ao vetor
void adicionarTime(BD_Times *bd, int id, const char *nome_do_time);

//Função para alocar a memória dos times
BD_Times *alocarMemoriaBDTimes();

//Função para liberar memória dos times, uma vez que foram alocados dinamicamente
void liberarBDTimes(BD_Times *bd);

//Função para atualizar informações/estatísticas dos times
void atualizarDadosTimes(BD_Partidas *dados_das_partidas, BD_Times *dados_dos_times);

//Função para imprimir tabela de classificação
void imprimirClassificacao(BD_Times *dados_times);

//Função para consultar um time baseado no prefixo/nome
void consultarTimes(BD_Times *dados);

#endif