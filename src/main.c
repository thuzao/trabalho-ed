#include <stdio.h>
#include "bd_times.h"
#include "bd_partidas.h"

int main(){
    BD_Times *dados_times = alocarMemoriaBDTimes();
    BD_Partidas *dados_partidas = alocarMemoriaBDPartidas();
    carregarTimes("times.csv", dados_times);
    carregarPartidas("partidas_completo.csv", dados_partidas);
    
    atualizarDadosTimes(dados_partidas, dados_times);

        // for (int i = 0; i < dados_times->qntd; i++){
        //     imprimirTime(dados_times->times[i]);
        // };

        // for (int j = 0; j < dados_partidas->qntd; j++){
        //     imprimirPartida(dados_partidas->partidas[j]);
        // };

    // consultarTimes(dados_times);

    consultarPartidas(dados_partidas, dados_times);
    liberarBDTimes(dados_times);
    liberarBDPartidas(dados_partidas);
    
    return 0;
}