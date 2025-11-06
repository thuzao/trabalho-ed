#include <stdio.h>
#include "bd_times.h"
#include "bd_partidas.h"

int main(){
    char opcao;

    BD_Times *dados_times = alocarMemoriaBDTimes();
    BD_Partidas *dados_partidas = alocarMemoriaBDPartidas();
    carregarTimes("times.csv", dados_times);
    carregarPartidas("partidas_completo.csv", dados_partidas);
    
    atualizarDadosTimes(dados_partidas, dados_times);
    while (1)
    {
        imprimirMenuPrincipal();
        scanf(" %c", &opcao);

        if(opcao == 'q' || opcao == 'Q') {
            printf("Saindo...\n");
            break; // sai do loop
        }

        switch(opcao) {
            case '1':
                consultarTimes(dados_times);
                break;
            case '2':
                consultarPartidas(dados_partidas, dados_times);
                break;
            case '3':
                imprimirNaoFoiImplementado();
                break;
            case '4':
                imprimirNaoFoiImplementado();
                break;
            case '5':
                imprimirNaoFoiImplementado();
                break;
            case '6':
                imprimirClassificacao(dados_times);
                break;
            default:
                printf("Opção inválida!\n");
        }
    }

    liberarBDTimes(dados_times);
    liberarBDPartidas(dados_partidas);
    
    return 0;
}