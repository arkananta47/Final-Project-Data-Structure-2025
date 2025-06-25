SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include
BIN_DIR := bin

DEBUG ?= 0
CFLAGS := -Wall -Wextra -Wpedantic
OPTIMIZATION := -O2
INCLUDE_FLAGS := -I$(INCLUDE_DIR)

# Get all source files and generate corresponding object paths
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

ifeq ($(DEBUG), 1)
	CFLAGS += -g
endif

# Main target - link all object files
main: $(OBJ_FILES) | dir
	gcc $(CFLAGS) $(OPTIMIZATION) $(INCLUDE_FLAGS) -o $(BIN_DIR)/$@ $^

# Rule for building object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | dir
	gcc $(CFLAGS) $(OPTIMIZATION) $(INCLUDE_FLAGS) -c $< -o $@

# Setup build and bin directories
dir:
ifeq ($(OS),Windows_NT)
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	@if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
else
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
endif

# Clean build and bin directories
clean:
ifeq ($(OS),Windows_NT)
	if exist "$(BUILD_DIR)" rmdir /S /Q "$(BUILD_DIR)"
	if exist "$(BIN_DIR)" rmdir /S /Q "$(BIN_DIR)"
else
	rm -rf $(BUILD_DIR) $(BIN_DIR)
endif

.PHONY:
	dir clean
