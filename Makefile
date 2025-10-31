# Nome do executável final
TARGET = trabalho-ed

# Compilador
CC = gcc

# Diretórios
INCLUDES_DIR = includes
SRC_DIR = src
MODELOS_DIR = $(SRC_DIR)/modelos

# Flags de compilação
CFLAGS = -Wall -Wextra -I$(INCLUDES_DIR) -I$(INCLUDES_DIR)/modelos

# Arquivos fonte
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/leitura.c \
       $(MODELOS_DIR)/bd_partidas.c \
       $(MODELOS_DIR)/bd_times.c \
       $(MODELOS_DIR)/partidas.c \
       $(MODELOS_DIR)/times.c

# Objetos gerados
OBJS = $(SRCS:.c=.o)

# Regra padrão
all: $(TARGET)

# Linkagem final
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Regra genérica para compilação dos .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos compilados
clean:
	rm -f $(OBJS)

# Limpeza completa (inclusive executável)
fclean: clean
	rm -f $(TARGET)

# Recompilar tudo do zero
re: fclean all

# Compila e executa o programa
run: all
	@./$(TARGET)
