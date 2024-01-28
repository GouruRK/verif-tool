CC=gcc
BUILD_DIR=bin
SRC_DIR=src
INCLUDE=-I./include
CFLAGS=-Wall -Wextra -Wfatal-errors -std=c17

EXEC=verif

SOURCES=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $^ -o $@ $(INCLUDE) $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir --parents $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

mrproper: clean
	rm -f $(EXEC)
