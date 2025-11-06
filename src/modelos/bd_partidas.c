#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bd_partidas.h"

void carregarPartidas(const char *bd_partidas, BD_Partidas *dados){
    //Lê o arquivo bd_times e armazena na variável
    FILE *arquivo = fopen(bd_partidas, "r");
    
    //Verificação se o arquivo foi lido corretamente
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo %s \n", bd_partidas);
        exit(1);
    };

    //Declarando variáveis para o tamanho máximo de linhas, o id, bem como o nome do time
    char linha[PARTIDAS_MAXIMO];
    int id;
    int time1;
    int time2;
    int gols_time1;
    int gols_time2;

    //Realiza a leitura do cabeçalho, posteriormente, será substituído o valor (Para que possamos ignorar)
    fgets(linha, sizeof(linha), arquivo);
    dados->qntd = 0;

     //Loop para armazenar os valores na estrutura
    while (fgets(linha, sizeof(linha), arquivo)) {
        //A condicional irá pegar o valor do id e o valor do char (Até 99 caracteres ou até achar o \n)
        if (sscanf(linha, "%d, %d, %d, %d, %d", &id, &time1, &time2, &gols_time1, &gols_time2) == 5) {
            adicionarPartida(dados, id, time1, time2, gols_time1, gols_time2);
        }
    }

    //Fechamento da leitura do arquivo
    fclose(arquivo);
}


void adicionarPartida(BD_Partidas *bd, int id, int time1, int time2, int gols_time1, int gols_time2){
    Partidas *partida = criarPartida(id, time1, time2, gols_time1, gols_time2);
    if (bd->qntd >= PARTIDAS_MAXIMO){
        printf("Capacidade máxima de partidas atingida! \n");
        exit(1);
    } else {
        bd->partidas[bd->qntd++] = partida;
    };
}

void imprimirTextoParaConsultarPartidas(){
    system("clear");
    printf("Escolha o modo de consulta: \n");
    printf("1 - Por time mandante \n");
    printf("2 - Por time visitante \n");
    printf("3 - Por time mandante ou visitante \n");
    printf("4 - Retornar ao menu principal \n");
    printf("\nDigite a opção desejada: ");
}

void consultarPartidas(BD_Partidas *dados_partidas, BD_Times *dados_times){
    int escolha;
    int partidas_impressas = 0;
    char prefixo[TIMES_MAXIMO];
    char encerramento;

    imprimirTextoParaConsultarPartidas();
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            //Verificar mandante
            system("clear");
            printf("Digite o nome ou prefixo do time: ");
            scanf("%s", prefixo);
            printf("\n");
            for (int i = 0; i < dados_partidas->qntd; i++){
                Partidas *partidas = dados_partidas->partidas[i];
                if (verificarMandante(prefixo, partidas, dados_times)){
                    imprimirPartida(partidas, dados_times);
                    partidas_impressas++;
                }
            }
            if (partidas_impressas == 0){
                printf("Nao foi encontrado nenhum time com este prefixo ou nome\n");
            }
            printf("\n");
            printf("\n");
            printf("Digite qualquer tecla para voltar ao menu principal: ");
            scanf("%s", &encerramento);
            break;

        case 2:
            //Verificar visitante
            system("clear");
            printf("Digite o nome ou prefixo do time: ");
            scanf("%s", prefixo);
            printf("\n");
            for (int i = 0; i < dados_partidas->qntd; i++){
                Partidas *partidas = dados_partidas->partidas[i];
                if (verificarVisitante(prefixo, partidas, dados_times)){
                    imprimirPartida(partidas, dados_times);
                    partidas_impressas++;
                }
            }
            if (partidas_impressas == 0){
                printf("Nao foi encontrado nenhum time com este prefixo ou nome\n");
            }
            printf("\n");
            printf("\n");
            printf("Digite qualquer tecla para voltar ao menu principal: ");
            scanf("%s", &encerramento);
            break;

        case 3:
            //Verificar mandante e visitante;
            system("clear");
            printf("Digite o nome ou prefixo do time: ");
            scanf("%s", prefixo);
            printf("\n");
            for (int i = 0; i < dados_partidas->qntd; i++){
                Partidas *partidas = dados_partidas->partidas[i];
                if (verificarMandante(prefixo, partidas, dados_times) || verificarVisitante(prefixo, partidas, dados_times)){
                    imprimirPartida(partidas, dados_times);
                    partidas_impressas++;
                }
            }
            if (partidas_impressas == 0){
                printf("Nao foi encontrado nenhum time com este prefixo ou nome\n");
            }
            printf("\n");
            printf("\n");
            printf("Digite qualquer tecla para voltar ao menu principal: ");
            scanf("%s", &encerramento);
            break;
            break;

        case 4:
            //Sair do menu
            printf("Saindo do menu de partidas...\n");
            system("clear");
            break;

        default:
            //Sair do menu
            printf("Opção inválida! Tente novamente.\n");
            break;
    }
}

BD_Partidas *alocarMemoriaBDPartidas(){
    BD_Partidas *bd = malloc(sizeof(BD_Partidas));
    if (bd == NULL) {
        printf("Erro ao alocar memória para estrutura de Partidas\n");
        exit(1);
    }
    return bd;
}

void liberarBDPartidas(BD_Partidas *bd) {
    for (int i = 0; i < bd->qntd; i++) {
        free(bd->partidas[i]);
    }
    free(bd);
}


void imprimirMenuPrincipal(){
    system("clear");
    printf("Sistema de Gerenciamento de Partidas \n");
    printf("\n");
    printf("1 - Consultar time \n");
    printf("2 - Consultar partida \n");
    printf("3 - Atualizar partida (Nao implementado ainda) \n");
    printf("4 - Remover partida (Nao implementado ainda) \n");
    printf("5 - Inserir partida (Nao implementado ainda) \n");
    printf("6 - Imprimir tabela de classificacao \n");
    printf("Q - Sair \n");
    printf("Escolha uma opção: ");
}
