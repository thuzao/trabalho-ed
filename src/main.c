#include <stdio.h>
#include "leitura.h"

int main(){
    BD_Times *dados = alocarMemoriaBDTimes();
    carregarTimes("times.csv", dados);
    
    liberarBDTimes(dados);
    
    return 0;
}