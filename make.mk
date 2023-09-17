# This Makefile compiles individual C files and places executables in a build directory

# Compiler to use
CC = gcc

# Flags for the compiler (optional)
CFLAGS = -Wall -g

# Source directory
SRC_DIR = src

# Build directory
BUILD_DIR = build

# List of source files
SRCS = $(wildcard $(SRC_DIR)/Capitulo*/listing*.c)

# List of source file basenames
BASENAMES = $(notdir $(SRCS))
EXECS = $(BASENAMES:.c=)

# Build targets
.PHONY: all clean

all: $(EXECS)

listing%: $(SRC_DIR)/%_4_1.c
	$(CC) $(CFLAGS) $< -o $(BUILD_DIR)/$@

clean:
	rm -rf $(BUILD_DIR)
