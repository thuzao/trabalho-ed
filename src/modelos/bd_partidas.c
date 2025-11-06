#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bd_partidas.h"

//Função para alocar a memória do BD_partidas
BD_Partidas *alocarMemoriaBDPartidas(){
    //Realiza a alocação dinâmica para o ponteiro bd do tipo BD_Partidas
    BD_Partidas *bd = malloc(sizeof(BD_Partidas));
    //Verifica se a alocação deu certo
    if (bd == NULL) {
        printf("Erro ao alocar memória para estrutura de Partidas\n");
        exit(1);
    }
    return bd; //Retorna o ponteiro bd que aponta para a estrutura do tipo BD_Partidas
}

//Função para liberar memória dos partidas, uma vez que foram alocados dinamicamente
void liberarBDPartidas(BD_Partidas *bd) {
    //Looping para liberar a memória de cada partida criado, acessando o vetor de ponteiros
    for (int i = 0; i < bd->qntd; i++) {
        free(bd->partidas[i]);
    }
    //Libera a memória da struct BD_Times
    free(bd);
}

//Função para carregar as partidas para o vetor dinâmico. Recebe como parâmetro o nome do arquivo e aonde que será salvo
void carregarPartidas(const char *bd_partidas, BD_Partidas *dados){
    //Lê o arquivo bd_times e armazena na variável
    FILE *arquivo = fopen(bd_partidas, "r");
    
    //Verificação se o arquivo foi lido corretamente
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo %s \n", bd_partidas);
        exit(1);
    };

    //Declarando variáveis para o tamanho máximo de linhas, o id, bem como os dados do time
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
            //Adiciona a partida específica ao vetor dinâmico dentor da estrutura BD_Partidas
            adicionarPartida(dados, id, time1, time2, gols_time1, gols_time2);
        }
    }
    //Fechamento da leitura do arquivo
    fclose(arquivo);
}

//Função que adiciona uma partida ao vetor
void adicionarPartida(BD_Partidas *bd, int id, int time1, int time2, int gols_time1, int gols_time2){
    //Cria uma instância da struct partida
    Partidas *partida = criarPartida(id, time1, time2, gols_time1, gols_time2);
    //Verificação se quantidade máxima de partidas foi atingida
    if (bd->qntd >= PARTIDAS_MAXIMO){
        printf("Capacidade máxima de partidas atingida! \n");
        exit(1);
    } else {
        //Adiciona a partida especficia ao vetor dinâmico contido na struct BD_Partidas
        bd->partidas[bd->qntd++] = partida;
    };
}

//Função para consultar partidas
void consultarPartidas(BD_Partidas *dados_partidas, BD_Times *dados_times){
    int escolha; //variavel para definir a escolha do usuário
    int partidas_impressas = 0; //declaracao para verificar se irá existir partida impresso ou nao
    char prefixo[TAMANHO_NOME_TIME]; //declaracao da variavel para prefixo
    char encerramento; //variavel extra para aplicar o "Digite qualquer valor para retornar ao menu"

    imprimirTextoParaConsultarPartidas();
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            //Verificar mandante
            //Armazenando prefixo digitado pelo usuário
            system("clear");
            printf("Digite o nome ou prefixo do time: ");
            scanf("%s", prefixo);
            printf("\n");
            //Loopping para percorrer o vetor contido na estrutura dados_partidas
            for (int i = 0; i < dados_partidas->qntd; i++){
                //Armazenando o ponteiro da partida especifica
                Partidas *partidas = dados_partidas->partidas[i];
                //Verifica se o mandante daquela partida tem o prefixo
                if (verificarMandante(prefixo, partidas, dados_times)){
                    imprimirPartida(partidas, dados_times); //imprime a partida
                    partidas_impressas++; //Informa que foi impresso partida
                }
            }
            //Caso não seja impresso nenhuma partida, será impresso essa mensagem
            if (partidas_impressas == 0){
                printf("Nao foi encontrado nenhum time com este prefixo ou nome\n");
            }
            //Parte de encerramento
            printf("\n");
            printf("\n");
            printf("Digite qualquer tecla para voltar ao menu principal: ");
            scanf("%s", &encerramento);
            break;

        case 2:
            //Verificar visitante
            //Armazenando prefixo digitado pelo usuário
            system("clear");
            printf("Digite o nome ou prefixo do time: ");
            scanf("%s", prefixo);
            printf("\n");
            //Loopping para percorrer o vetor contido na estrutura dados_partidas
            for (int i = 0; i < dados_partidas->qntd; i++){
                //Armazenando o ponteiro da partida especifica
                Partidas *partidas = dados_partidas->partidas[i];
                //Verifica se o visitante daquela partida tem o prefixo
                if (verificarVisitante(prefixo, partidas, dados_times)){
                    imprimirPartida(partidas, dados_times); //Imprime a partida
                    partidas_impressas++; //Informa que foi impresso partida
                }
            }
            //Caso não seja impresso nenhuma partida, será impresso essa mensagem
            if (partidas_impressas == 0){
                printf("Nao foi encontrado nenhum time com este prefixo ou nome\n");
            }
            //Parte de encerramento
            printf("\n");
            printf("\n");
            printf("Digite qualquer tecla para voltar ao menu principal: ");
            scanf("%s", &encerramento);
            break;

        case 3:
            //Verificar mandante e visitante;
            //Armazenando prefixo digitado pelo usuário
            system("clear");
            printf("Digite o nome ou prefixo do time: ");
            scanf("%s", prefixo);
            printf("\n");
            //Loopping para percorrer o vetor contido na estrutura dados_partidas
            for (int i = 0; i < dados_partidas->qntd; i++){
                //Armazenando o ponteiro da partida especifica
                Partidas *partidas = dados_partidas->partidas[i];
                //Verifica se o visitante ou o mandante daquela partida tem o prefixo
                if (verificarMandante(prefixo, partidas, dados_times) || verificarVisitante(prefixo, partidas, dados_times)){
                    imprimirPartida(partidas, dados_times); //Imprime a partida
                    partidas_impressas++; //Informa que foi impresso partida
                }
            }
            //Caso não seja impresso nenhuma partida, será impresso essa mensagem
            if (partidas_impressas == 0){
                printf("Nao foi encontrado nenhum time com este prefixo ou nome\n");
            }
            //Parte de encerramento
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
            //Imprimi a opcao invalida e pede para tentar novamente
            printf("Opção inválida! Tente novamente.\n");
            break;
    }
}

//Função para criar para imprimir o texto para consultar
void imprimirTextoParaConsultarPartidas(){
    system("clear");
    printf("Escolha o modo de consulta: \n");
    printf("1 - Por time mandante \n");
    printf("2 - Por time visitante \n");
    printf("3 - Por time mandante ou visitante \n");
    printf("4 - Retornar ao menu principal \n");
    printf("\nDigite a opção desejada: ");
}


//Função que apresenta o menu geral
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
