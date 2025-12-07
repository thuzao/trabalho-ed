#ifndef BD_PARTIDAS_H
#define BD_PARTIDAS_H

#include "partidas.h"
#include "bd_times.h"

// Nó da lista encadeada de partidas
typedef struct PartidaNode {
    Partidas partida;
    struct PartidaNode *proximo;
} PartidaNode;

// Estrutura do BD de partidas
typedef struct BD_Partidas {
    PartidaNode *inicio;
} BD_Partidas;

// Aloca memória
BD_Partidas *alocarMemoriaBDPartidas();

// Libera memória
void liberarBDPartidas(BD_Partidas *bd);

// Carregar arquivo CSV
void carregarPartidas(const char *arquivo, BD_Partidas *dados);

// Adicionar partida (interna)
void adicionarPartida(BD_Partidas *bd, int id, int time1, int time2, int gols1, int gols2);

// Buscar partida por ID
PartidaNode *buscarPartidaPorID(BD_Partidas *bd, int id);

// Consulta completa (menu igual ao TP)
void consultarPartidas(BD_Partidas *dados_partidas, BD_Times *dados_times);

// Inserir partida (fluxo completo do TP)
void inserirPartida(BD_Partidas *dados_partidas, BD_Times *dados_times);

// Atualizar partida (fluxo completo)
void atualizarPartida(BD_Partidas *dados_partidas, BD_Times *dados_times);

// Remover partida (fluxo completo)
void removerPartida(BD_Partidas *dados_partidas, BD_Times *dados_times);

// Gerar ID automático
int gerarNovoID(BD_Partidas *bd);

// Salvar CSV
void salvarPartidasCSV(const char *arquivo, BD_Partidas *dados);

#endif
