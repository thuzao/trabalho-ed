# =========================================================
#   Projeto: trabalho-ed
#   Compilador e diretórios
# =========================================================

TARGET = trabalho-ed
CC = gcc

INCLUDES_DIR = includes
SRC_DIR = src
MODELOS_DIR = $(SRC_DIR)/modelos

# =========================================================
#   Flags de compilação
# =========================================================

CFLAGS = -Wall -Wextra -I$(INCLUDES_DIR) -I$(INCLUDES_DIR)/modelos

# =========================================================
#   Fontes e objetos
# =========================================================

SRC_FILES = \
    $(SRC_DIR)/main.c \
    $(MODELOS_DIR)/bd_partidas.c \
    $(MODELOS_DIR)/bd_times.c \
    $(MODELOS_DIR)/partidas.c \
    $(MODELOS_DIR)/times.c

OBJ_FILES = $(SRC_FILES:.c=.o)

# =========================================================
#   Regras principais
# =========================================================

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	@echo "🔗 Ligando objetos..."
	$(CC) $(OBJ_FILES) -o $(TARGET)
	@echo "✅ Compilação concluída com sucesso!"

# =========================================================
#   Regras genéricas
# =========================================================

%.o: %.c
	@echo "🧩 Compilando $< ..."
	$(CC) $(CFLAGS) -c $< -o $@

# =========================================================
#   Limpeza
# =========================================================

clean:
	@echo "🧹 Limpando arquivos objeto..."
	rm -f $(OBJ_FILES)

fclean: clean
	@echo "🗑 Removendo executável..."
	rm -f $(TARGET)

re: fclean all

# =========================================================
#   Extras
# =========================================================

run: all
	@echo "🚀 Executando programa..."
	./$(TARGET)
