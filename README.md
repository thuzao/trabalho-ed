# Sistema de Gerenciamento de Times e Partidas

## 📚 Descrição do Projeto

Este projeto foi desenvolvido pelos estudantes **Arthur Oliveira Marques da Silva (20242BSI0087)** e **Gabriel Alves da Conceição Abreu (20242BSI0168)** como parte da disciplina **Estrutura de Dados** do IFES (Campus Serra).

O sistema permite gerenciar **times e partidas de um campeonato**, utilizando **Listas Encadeadas (Linked Lists)** para manipulação dinâmica de dados e persistência em arquivos CSV. Ele suporta operações de **CRUD** (Inserção, Consulta, Atualização e Remoção) com recálculo automático das estatísticas dos times.

---

## 🗂 Estrutura do Projeto

```text
TRABALHO-ED/
│
├── includes/
│   ├── bd_partidas.h      # Cabeçalho da lista encadeada de partidas
│   ├── bd_times.h         # Cabeçalho da lista encadeada de times
│   ├── partidas.h         # Estrutura e funções auxiliares de Partida
│   ├── times.h            # Estrutura e funções auxiliares de Time
│
├── src/
│   ├── main.c             # Menu principal e controle de fluxo
│   └── modelos/
│       ├── bd_partidas.c  # Implementação da lista e manutenção de partidas
│       ├── bd_times.c     # Implementação da lista e estatísticas de times
│       ├── partidas.c     # Funções auxiliares de partidas
│       ├── times.c        # Funções auxiliares de times
│
├── Makefile               # Automação de compilação
├── partidas_completo.csv  # Base de dados de partidas
├── times.csv              # Base de dados de times
└── README.md              # Documentação do projeto
```

---

## 🧠 Estruturas de Dados Principais

### 1. TAD Time (`times.h`)

* Representa um clube.
* **Dados:** ID, nome, vitórias, derrotas, empates, gols a favor, gols contra e saldo de gols.
* **Responsabilidade:** Armazenar o estado atual de cada time.

### 2. TAD Partida (`partidas.h`)

* Representa um jogo entre dois times.
* **Dados:** ID da partida, IDs dos times (mandante e visitante) e placares.
* **Responsabilidade:** Determinar o resultado e atualizar estatísticas dos times.

### 3. TAD BDTimes (`bd_times.h`)

* Lista encadeada para gerenciar todos os times.
* **Principais funções:**

  * `carregarTimes`: Lê times do CSV.
  * `ordenarTimes`: Ordena a tabela por pontos, vitórias e saldo de gols.
  * `buscarTimePorID`: Localiza um time específico.

### 4. TAD BDPartidas (`bd_partidas.h`)

* Lista encadeada para gerenciar todas as partidas.
* **Principais funções:**

  * `inserirPartida`, `atualizarPartida`, `removerPartida`: CRUD de partidas.
  * `salvarPartidasCSV`: Persiste alterações no arquivo CSV.

---

## 🧱 Estratégias de Implementação

* **Recálculo Total:** Ao inserir, remover ou atualizar partidas, todas as estatísticas dos times são zeradas e recalculadas a partir da lista completa de partidas, garantindo consistência.
* **Ordenação da Tabela:** Utiliza **Bubble Sort** sobre a lista encadeada de times. Critério: Pontos Ganhos > Vitórias > Saldo de Gols.
* **IDs Automáticos:** A cada nova partida, o sistema gera o próximo ID disponível.
* **Interface Interativa:** Limpeza de tela e pausas estratégicas para melhor navegação.

---

## 🧩 Funcionalidades

* Consultar **times** por nome ou prefixo e exibir estatísticas detalhadas.
* Consultar **partidas** filtrando por mandante, visitante ou ambos.
* **Inserir** nova partida com validação de times.
* **Atualizar** placares de partidas existentes.
* **Remover** partidas e atualizar estatísticas automaticamente.
* Exibir **classificação completa** do campeonato.
* Salvar alterações em **CSV** ao encerrar o programa.

---

## 💻 Como Compilar e Executar

### Pré-requisitos

* Compilador `gcc`
* Utilitário `make`
* Sistema Linux/Unix recomendado

### Comandos

| Objetivo                      | Comando       |
| ----------------------------- | ------------- |
| Compilar o projeto            | `make`        |
| Executar o sistema            | `make run`    |
| Limpar arquivos objeto (.o)   | `make clean`  |
| Limpar tudo (executável + .o) | `make fclean` |
| Recompilar do zero            | `make re`     |

O executável gerado será chamado `trabalho-ed`.

---

## 🎯 Considerações Finais

Este projeto demonstra a aplicação prática de **estruturas de dados dinâmicas** em C, combinando **listas encadeadas** com persistência em arquivos CSV e uma interface de usuário simples, porém funcional. O foco principal foi garantir **robustez, consistência e modularidade** do código.
