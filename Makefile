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
SRCS := $(shell find src -type f -name 'listing_*.*')

# List of source file basenames
BASENAMES = $(notdir $(SRCS))
EXECS = $(BASENAMES:.c=)

# Build targets
.PHONY: all clean

listing_1%:
	mkdir -p build/src/Capitulo_1/
	$(CC) $(CFLAGS) "src/Capitulo_1/listing_1.1.c" "src/Capitulo_1/listing_1.2.cpp" "src/Capitulo_1/listing_1.3.hpp" -o "build/src/Capitulo_1/listing_1.1"

listing_2%:
	$(eval listing = $(@))
	$(eval dir = $(shell find src -type f -name $(listing).c))
	$(eval parent_dir = $(shell dirname $(dir)))
	$(eval new_dir = $(BUILD_DIR)/$(parent_dir))
	mkdir -p $(new_dir)
	$(CC) $(dir) -o "$(new_dir)/$@" $(CFLAGS)

listing_3%:
	$(eval listing = $(@))
	$(eval dir = $(shell find src -type f -name $(listing).c))
	$(eval parent_dir = $(shell dirname $(dir)))
	$(eval new_dir = $(BUILD_DIR)/$(parent_dir))
	mkdir -p $(new_dir)
	$(CC) $(CFLAGS) $(dir) -o "$(new_dir)/$@"

listing_4%:
	$(eval listing = $(@))
	$(eval dir = $(shell find src -type f -name $(listing).*))
	$(eval parent_dir = $(shell dirname $(dir)))
	$(eval new_dir = $(BUILD_DIR)/$(parent_dir))
	mkdir -p $(new_dir)
	$(CC) $(CFLAGS) $(dir) -o "$(new_dir)/$@"

$(eval DIRS := $(shell find src -type f -name 'listing*' -exec basename {} \;))

all: $(DIRS)
	@for file in $^; do \
		$(MAKE) "$$file"; \
	done

clean:
	rm -rf $(BUILD_DIR)
