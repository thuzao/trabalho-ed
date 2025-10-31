#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leitura.h"

#include "../includes/modelos/bd_times.h"
#include "../includes/modelos/bd_partidas.h"

void carregarTimes(const char *bd_times, BD_Times *dados){
    //Lê o arquivo bd_times e armazena na variável
    FILE *arquivo = fopen(bd_times, "r");
    
    //Verificação se o arquivo foi lido corretamente
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo %s \n", bd_times);
        exit(1);
    };

    //Declarando variáveis para o tamanho máximo de linhas, o id, bem como o nome do time
    char linha[TIMES_MAXIMO];
    int id;
    char nome[TAMANHO_NOME_TIME];

    //Realiza a leitura do cabeçalho, posteriormente, será substituído o valor (Para que possamos ignorar)
    fgets(linha, sizeof(linha), arquivo);
    dados->qntd = 0;

    //Loop para armazenar os valores na estrutura
    while (fgets(linha, sizeof(linha), arquivo)) {
        //A condicional irá pegar o valor do id e o valor do char (Até 99 caracteres ou até achar o \n)
        if (sscanf(linha, "%d,%99[^\n]", &id, nome) == 2) {
            adicionarTime(dados, id, nome);
        }
    }

    //Fechamento da leitura do arquivo
    fclose(arquivo);
}