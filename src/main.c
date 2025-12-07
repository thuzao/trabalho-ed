#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bd_times.h"
#include "bd_partidas.h"
#include "partidas.h"
#include "times.h"

#define ARQ_TIMES "times.csv"
#define ARQ_PARTIDAS "partidas_completo.csv"

void imprimirMenuPrincipal() {
    printf("=========================================\n");
    printf("      SISTEMA DE CAMPEONATO - PARTE 2    \n");
    printf("=========================================\n");
    printf("1 - Consultar Time\n");
    printf("2 - Consultar Partidas\n");
    printf("3 - Atualizar Partida\n");
    printf("4 - Remover Partida\n");
    printf("5 - Inserir Nova Partida\n");
    printf("6 - Imprimir Tabela de Classificacao\n");
    printf("Q - Sair do Sistema\n");
    printf("=========================================\n");
    printf("Digite sua opcao: ");
}

int main() {

    BD_Times *dados_times = alocarMemoriaBDTimes();
    BD_Partidas *dados_partidas = alocarMemoriaBDPartidas();

    carregarTimes(ARQ_TIMES, dados_times);
    carregarPartidas(ARQ_PARTIDAS, dados_partidas);

    //Primeiro cálculo
    resetarEstatisticas(dados_times);
    atualizarDadosTimes(dados_partidas, dados_times);

    char opcao;

    while (1) {

        imprimirMenuPrincipal();
        scanf(" %c", &opcao);

        switch (opcao) {

            case '1':
                consultarTimes(dados_times);
                break;

            case '2':
                consultarPartidas(dados_partidas, dados_times);
                break;

            case '3':
                atualizarPartida(dados_partidas, dados_times);
                break;

            case '4':
                removerPartida(dados_partidas, dados_times);
                break;

            case '5':
                inserirPartida(dados_partidas, dados_times);
                break;

            case '6':
                imprimirClassificacao(dados_times);
                break;

            case 'Q':
            case 'q':
                salvarPartidasCSV(ARQ_PARTIDAS, dados_partidas);
                printf("Encerrando o sistema...\n");

                liberarBDPartidas(dados_partidas);
                liberarBDTimes(dados_times);
                exit(0);

            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    }

    return 0;
}
