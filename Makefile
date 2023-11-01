# DIRETORIOS
SRC_DIR = src
OBJ_DIR = build
INC_DIR = include
MODULES_DIR = modules
INC_SUBMODULES := $(shell find $(MODULES_DIR) -type d -name include)
INC_SUBMODULES := $(patsubst %,-I %, $(INC_SUBMODULES)) # Adiciona "-I" em cada caminho encontrado
BIN_DIR = bin
TST_DIR = $(SRC_DIR)/tests
LIB_DIR = $(INC_DIR)/lib

# NOME DOS EXECUTAVEIS
PROGRAM_NAME = program
TEST_NAME = test

# CONFIGURAÇÕES DO COMPILADOR
OS_NAME := $(shell grep -oP '(?<=^NAME=).+' /etc/os-release | tr -d '"')

ifeq ($(OS_NAME), Ubuntu)
    # Please, install g++12: sudo apt install g++-12
	CC = g++-12

else
	CC = g++

endif

LIBS = -lm
CFLAGS = --std=c++20 -O0 -Wall

# ARQUIVOS
MAIN = $(OBJ_DIR)/main.o

## Objeter o nome de todos os arquivos .o
PROGRAM_OBJS := $(shell find $(SRC_DIR) -type f -name "*.cc" ! -name "main.cc" ! -name "*test.cc" ! -path "$(MODULES_DIR)/*" -exec echo '$(OBJ_DIR)/{}' \; | sed 's/src\///;s/\/\.\//\//;s/\.cc/.o/')

## Obter o nome de todos os arquivos .o de todos os submódulos
SUB_MODULES_OBJS := $(shell find $(MODULES_DIR) -type f -name "*.cc" ! -name "main.cc" ! -name "*test.cc" | sed 's/src\//$(OBJ_DIR)\//;s/\.cc/.o/')

## Obter o nome de todos os arquivos .o de teste
TEST_OBJS := $(shell find $(TST_DIR) -type f -name "*.cc" -exec echo '$(OBJ_DIR)/{}' \; | sed 's/src\/tests\///;s/\/\.\//\//;s/\.cc/.o/')

# CASES
build: $(OBJ_DIR)/$(PROGRAM_NAME)

submodules:
	git submodule update --remote --recursive

	@echo "Building submodules..."
	@for submodule in $(wildcard modules/*); do \
		echo "Building $$submodule..."; \
		(cd $$submodule && make clean && make submodules || true && make); \
	done
	@echo "Submodules built"

run: build
	$(BIN_DIR)/$(PROGRAM_NAME) --file

run_interactive: build
	$(BIN_DIR)/$(PROGRAM_NAME)

tests: $(OBJ_DIR)/$(TEST_NAME)
	$(BIN_DIR)/$(TEST_NAME)

$(OBJ_DIR)/$(TEST_NAME): $(TEST_OBJS) $(PROGRAM_OBJS)
	$(CC) $(CFLAGS) $(LIBS) $(TEST_OBJS) $(PROGRAM_OBJS) $(SUB_MODULES_OBJS) -o $(BIN_DIR)/$(TEST_NAME)

$(OBJ_DIR)/$(PROGRAM_NAME): $(PROGRAM_OBJS) $(MAIN)
	$(CC) $(CFLAGS) $(LIBS) $(PROGRAM_OBJS) $(SUB_MODULES_OBJS) $(MAIN) -o $(BIN_DIR)/$(PROGRAM_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc $(INC_DIR)/%.h
	$(CC) -c $(CFLAGS) $(LIBS) $< -I $(INC_DIR) $(INC_SUBMODULES) -o $@

$(OBJ_DIR)/%.o: $(TST_DIR)/%.cc
	$(CC) -c $(CFLAGS) $(LIBS) $< -I $(INC_DIR) $(INC_SUBMODULES) -I $(LIB_DIR) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CC) -c $(CFLAGS) $(LIBS) $< -I $(INC_DIR) $(INC_SUBMODULES) -o $@

valgrind: build tests
	valgrind --leak-check=full $(BIN_DIR)/$(TEST_NAME) > /dev/null
	valgrind --leak-check=full $(BIN_DIR)/$(PROGRAM_NAME) --file < src/tests/inputs/expression_size-1000.txt > /dev/null

clean:
	rm -f $(BIN_DIR)/* $(OBJ_DIR)/* gmon.out arvore.txt data.dat grafico.png
