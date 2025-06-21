SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include
BIN_DIR := bin

DEBUG ?= 0
CFLAGS := -Wall -Wextra -Wpedantic
OPTIMIZATION := -O2
INCLUDE_FLAGS := -Iinclude

OBJS := $(patsubst %.c,%.o, $(wildcard $(SRC_DIR)/*.c))

ifeq ($(debug), 1)
	CFLAGS := $(CFLAGS) -g
endif

main: $(OBJS)
	gcc $(CFLAGS) $(OPTIMIZATION) $(INCLUDE_FLAGS) -o $(BIN_DIR)/$@ $(patsubst %, build/%, $(OBJS))

$(OBJS): dir
	@mkdir -p $(BUILD_DIR)/$(@D)
	gcc $(CFLAGS) $(OPTIMIZATION) $(INCLUDE_FLAGS) -o $(BUILD_DIR)/$@ -c $*.c

# Setup build and bin directories
dir:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

# Clean build and bin directories
clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: dir clean
