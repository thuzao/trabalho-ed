# Trabalho Prático — Estrutura de Dados
### Sistema de Gerenciamento de Times e Partidas

Este projeto foi desenvolvido como parte da disciplina **Estrutura de Dados**, com o objetivo de aplicar os conceitos de **TADs (Tipos Abstratos de Dados)**, **ponteiros**, **modularização** e **manipulação de arquivos** em linguagem C.  

O sistema simula o gerenciamento de um **campeonato de futebol**, permitindo a exibição e classificação de times e partidas, a partir da leitura de um arquivo utilizando estruturas dinâmicas e organização modular de código.

---

## 📁 Estrutura do Projeto

O projeto está organizado da seguinte forma:

```
TRABALHO-ED/
│
├── includes/
│   ├── bd_partidas.h
│   ├── bd_times.h
│   ├── partidas.h
│   ├── times.h
│
├── src/
│   ├── main.c
│   └── modelos/
│       ├── bd_partidas.c
│       ├── bd_times.c
│       ├── partidas.c
│       ├── times.c
│
├── Makefile
└── README.md
```

---

## ⚙️ Estrutura dos Componentes

- **`main.c`**  
  Contém o fluxo principal do programa, o menu interativo e a integração entre os módulos do sistema.

- **`bd_times.h/c`**  
  Define o TAD responsável por armazenar e manipular os dados dos times, incluindo identificação, nome, vitórias, empates, derrotas, gols e pontuação.

- **`bd_partidas.h/c`**  
  Define o TAD responsável pelo gerenciamento das partidas, com dados como identificadores dos times, gols e resultados.

- **`partidas.c` e `times.c`**  
  Implementam funções auxiliares para manipular e exibir informações dos TADs, além de atualizar as estatísticas de cada time conforme os resultados.

- **`Makefile`**  
  Automatiza o processo de compilação, limpeza e execução do sistema.  

---

## 🧠 Conceitos Utilizados

- Tipos Abstratos de Dados (TADs)  
- Alocação dinâmica de memória  
- Ponteiros e estruturas compostas  
- Manipulação de arquivos texto (CSV)  
- Modularização e organização de código  
- Controle de fluxo com menus interativos  

---

## 🧩 Funcionalidades do Sistema

O sistema foi projetado para gerenciar times e partidas de um campeonato de forma simples e modular.  
As principais funcionalidades implementadas são:

- **Carregamento de dados**  
  - Leitura automática dos arquivos de times e partidas ao iniciar o sistema.  
  - Verificação de erros ao abrir e ler os arquivos.  

- **Exibição de times cadastrados**  
  - Lista todos os times registrados com seus respectivos IDs, nomes e estatísticas.  
  - Exibição organizada em formato de tabela no terminal.  

- **Exibição de partidas realizadas**  
  - Mostra todas as partidas carregadas, indicando os times participantes, placares e resultados.  

- **Cálculo de pontuação e estatísticas**  
  - Atualiza a pontuação de cada time de acordo com as regras (3 pontos por vitória, 1 por empate).  
  - Calcula e armazena gols marcados, sofridos, saldo de gols e aproveitamento.  

- **Classificação dos times**  
  - Ordena os times com base na pontuação total e exibe a tabela de classificação.  
  - Implementação de algoritmo de ordenação próprio, sem uso de bibliotecas externas.  

- **Interface de menu interativo**  
  - Apresenta um menu com opções numeradas (1, 2, 3...) e saída através da tecla “q”.  
  - Uso de limpeza de tela para manter o terminal organizado durante a execução.  

- **Estrutura modular e reutilizável**  
  - Cada funcionalidade é separada em seu próprio módulo, facilitando manutenção e extensão do sistema.  

---

## 💻 Compilação e Execução

O projeto utiliza um **Makefile** para simplificar a compilação e execução.  

### Comandos principais:

| Ação | Comando |
|------|----------|
| Compilar o projeto | `make` |
| Executar o programa | `make run` |
| Limpar apenas arquivos objeto | `make clean` |
| Limpar arquivos objeto e o executável | `make fclean` |
| Remover binário e recompila | `make re` |

O executável final gerado tem o nome **`trabalho-ed`**.

---

## 🧱 Decisões de Implementação

- Organização modular tentou-se seguir boas práticas de desenvolvimento em C.  
- Carregamento de dados apenas no início e liberação da memória ao encerrar.  
- Interface limpa com uso de `system("clear")` para melhor legibilidade.  
- Comentários explicativos e consistentes em todos os módulos.
- Separação do código baseado nos TADs

---

## 🪟 Ambiente de Desenvolvimento

- **Sistema Operacional:** Ubuntu Mint  
- **Compilador:** GCC  
- **Execução via Terminal:** compatível com sistemas baseados em Linux  

---
