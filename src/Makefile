# Define el compilador y las opciones de compilación
CC = gcc
CXX = g++
CFLAGS = -Wall -Werror
CXXFLAGS = -Wall -Werror

# Nombre del ejecutable final
TARGET = mi_programa

# Lista de archivos de origen .c y .cpp
SRC_C = $(wildcard *.c)
SRC_CPP = $(wildcard *.cpp)

# Lista de archivos objeto generados a partir de los archivos de origen
OBJ_C = $(SRC_C:.c=.o)
OBJ_CPP = $(SRC_CPP:.cpp=.o)

# Regla por defecto: compila todo
all: $(TARGET)

# Regla para compilar el ejecutable final
$(TARGET): $(OBJ_C) $(OBJ_CPP)
	$(CXX) $(CFLAGS) $(CXXFLAGS) $^ -o $@

# Regla para compilar archivos .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para compilar archivos .cpp
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Borra los archivos objeto y el ejecutable
clean:
	rm -f $(OBJ_C) $(OBJ_CPP) $(TARGET)

.PHONY: all clean
