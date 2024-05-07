GCC = gcc

SRC_DIR = src
INCLUDE_DIR = include
LIB_DIR = lib
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(LIB_DIR)/%.o, $(SRCS))
TARGET = $(BIN_DIR)/Test

all: compile run

compile: $(TARGET)

$(TARGET): $(OBJS)
	$(GCC) $^ -o $@ -lm

$(LIB_DIR)/%.o: $(SRC_DIR)/%.c
	$(GCC) -I$(INCLUDE_DIR) -c $< -o $@

run:
	$(TARGET)

clean:
	rm -f $(LIB_DIR)/*.o $(TARGET)