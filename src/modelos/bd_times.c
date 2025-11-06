#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "time.h"
#include "partidas.h"
#include "bd_partidas.h"
#include "bd_times.h"

//Realiza a alocação de memória para a estrutura que aloca todos os times
BD_Times *alocarMemoriaBDTimes() {
    //Realiza a alocação dinâmica para o ponteiro bd do tipo BD_Times
    BD_Times *bd = malloc(sizeof(BD_Times));
    //Verifica se a alocação deu certo
    if (bd == NULL) {
        printf("Erro ao alocar memória para estrutura de Times\n");
        exit(1);
    }
    return bd; //Retorna o ponteiro bd que aponta para a estrutura do tipo BD_Times
}
//Função para liberar memória dos times, uma vez que foram alocados dinamicamente
void liberarBDTimes(BD_Times *bd) {
    //Looping para liberar a memória de cada time criado, acessando o vetor de ponteiros
    for (int i = 0; i < bd->qntd; i++) {
        free(bd->times[i]);
    }
    //Libera a memória da struct BD_Times
    free(bd);
}
//Função para carregar os times para o vetor dinâmico. Recebe como parâmetro o nome do arquivo e aonde que será salvo
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
            adicionarTime(dados, id, nome);//Adiciona o time especifico ao vetor BD_Times
        }
    }

    //Fechamento da leitura do arquivo
    fclose(arquivo);
}

//Função que adiciona um time ao vetor
void adicionarTime(BD_Times *bd, int id, const char *nome_do_time){
    //Cria uma instância da struct times
    Times *time = criarTime(id, nome_do_time);
    //Verifica se a capacidade máxima do time foi atingida
    if (bd->qntd >= TIMES_MAXIMO){
        printf("Capacidade máxima de times atingida! \n");
        exit(1);
    } else {
        bd->times[bd->qntd++] = time;
    };
}

//Função para atualizar informações/estatísticas dos times
void atualizarDadosTimes(BD_Partidas *dados_das_partidas, BD_Times *dados_dos_times){
    //Loopping para acessar cada time e informações no vetor dentro de dados_das_partidas
    for (int i = 0; i < dados_das_partidas->qntd; i++){
        //Salvar as informações da partida i em partida verificada
        Partidas *partida_verificada = dados_das_partidas->partidas[i];
        
        //Salva os dois times envolvidos na partida verificada
        Times *time1 = dados_dos_times->times[partida_verificada->time1];
        Times *time2 = dados_dos_times->times[partida_verificada->time2];
        
        //Implementando informações de gols para o time mandante
        adicionarGolsMarcados(time1, partida_verificada->gols_time1);
        adicionarGolsSofridos(time1, partida_verificada->gols_time2);
        
        //Implementando informações de gols para o time visitante
        adicionarGolsMarcados(time2, partida_verificada->gols_time2);
        adicionarGolsSofridos(time2, partida_verificada->gols_time1);
        
        //Verificação se o time venceu, empatou ou perdeu
        if (!verificarSeFoiEmpate(partida_verificada)){
            atualizarVencedor(partida_verificada, time1, time2); //Atribui quem venceu
        } else {
            //Atribui a informação de empates da os dois times
            time1->empates++; 
            time2->empates++;
        }
        calcularPontuacao(time1); //Calcula a pontuacao atualizada do time1
        calcularPontuacao(time2); //Calcula a pontuacao atualizada do time2
    }
}

//Função para imprimir tabela de classificação
void imprimirClassificacao(BD_Times *dados_times){
    char encerramento; //variavel extra para aplicar o "Digite qualquer valor para retornar ao menu"
    system("clear"); //limpa o console
    imprimirCabecalhoDeDadosDosTimes(); //Imprime o cabeçalho dos times
    //Loopping para imprimir a informação de cada time (nome, vitorias, pontuacao e etc)
    for (int i = 0; i < dados_times->qntd; i++){
        imprimirTime(dados_times->times[i]);
    }
    //Parte para encerramento da funcionalidade
    printf("\n");
    printf("\n");
    printf("Digite qualquer tecla para voltar ao menu principal: ");
    scanf("%s", &encerramento);
    system("clear");
}

//Função para consultar um time baseado no prefixo/nome
void consultarTimes(BD_Times *dados){
    char encerramento; //variavel extra para aplicar o "Digite qualquer valor para retornar ao menu"
    char prefixo[TIMES_MAXIMO]; //declaracao da variavel para prefixo
    int times_impressos = 0; //declaracao para verificar se irá existir time impresso ou nao
    system("clear");
    //Scanf para digitar o nome ou prefixo do time
    printf("Digite o nome ou prefixo do time: ");
    scanf("%s", prefixo); 
    printf("\n");
    //Loopping para verificar o prefixo e imprimir caso seja igual
    for (int i = 0; i < dados->qntd; i++){
        //verificao do prefixo se é igual ou nao
        if (verificarPreFixoDoTime(dados->times[i]->nome_do_time, prefixo)){
            times_impressos++;
            if (times_impressos <= 1){
                imprimirCabecalhoDeDadosDosTimes();
            }
            imprimirTime(dados->times[i]);

        };
    };
    //Apresentando que nenhum time foi impresso
    if (times_impressos == 0){
        printf("Nao foi encontrado nenhum time com este prefixo ou nome \n");
    };
    //Parte para encerramento da funcionalidade
    printf("\n");
    printf("\n");
    printf("Digite qualquer tecla para voltar ao menu principal: ");
    scanf("%s", &encerramento);
    system("clear");
}
