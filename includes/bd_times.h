#ifndef BD_TIMES_H
#define BD_TIMES_H

#include "times.h"
#include "bd_partidas.h"

#define TIMES_MAXIMO 100
typedef struct 
{
    Times *times[TIMES_MAXIMO];
    int qntd;

} BD_Times;

//Função para carregar os times para o vetor dinâmico. Recebe como parâmetro o nome do arquivo e aonde que será salvo
void carregarTimes(const char *bd_times, BD_Times *dados);

//Função que adiciona um time ao vetor
void adicionarTime(BD_Times *bd, int id, const char *nome_do_time);

//Função que verificar se já existe time
int existeTime(BD_Times *bd, char *nome_do_time);

//Função para alocar a memória dos times
BD_Times *alocarMemoriaBDTimes();

//Função para liberar memória dos times, uma vez que foram alocados dinamicamente
void liberarBDTimes(BD_Times *bd);

//Função para atualizar informações/estatísticas dos times
void atualizarDadosTimes(BD_Partidas *dados_das_partidas, BD_Times *dados_dos_times);

//Função para atualizar informações do vencedor e do perdedor
void atualizarVencedor(Partidas *partida, Times *time1, Times *time2);

//Função para consultar um time baseado no prefixo/nome
void consultarTimes(BD_Times *dados);



#endif