#include <stdio.h>
#include "leitura.h"

int main(){
    BD_Times *dados = alocarMemoriaBDTimes();
    carregarTimes("times.csv", dados);
    
    for (int i = 0; i < dados->qntd; i++){
        imprimirTime(dados->times[i]);
    }

    liberarBDTimes(dados);
    
    return 0;
}