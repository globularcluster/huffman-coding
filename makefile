# Makefile genérico.
# Compila e linka todos arquivos adicionados em seus respectivos
# diretórios.

# Diretórios
SRCDIR:= ./src
OBJDIR:= ./obj
HDRDIR:= ./include

EXECUTABLE:= huffman-coding

# Mágica que faz selecionar todos arquivos
CPP_FILES := $(wildcard $(SRCDIR)/*.cpp)
OBJ_FILES := $(addprefix $(OBJDIR)/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS :=
CC_FLAGS := -std=c++11 -Wall -I $(HDRDIR)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	g++ $(LD_FLAGS) -o $@ $^

obj/%.o: src/%.cpp
	@mkdir -p obj
	g++ $(CC_FLAGS) -c -o $@ $<

# Limpa .obj's e exec. Execute com: make clean
clean:
	rm -f  $(OBJDIR)/*.o $(EXECUTABLE)