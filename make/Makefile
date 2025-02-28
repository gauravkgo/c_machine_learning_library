
PROJ_DIR = $(shell dirname $(shell pwd))
ABSOLUTE_PROJ_DIR = $(shell dirname $(shell pwd))
SRC_DIR = $(PROJ_DIR)/src
INC_DIR = $(PROJ_DIR)/include
BIN_DIR = $(ABSOLUTE_PROJ_DIR)/bin
OBJ_DIR = $(BIN_DIR)/obj
LIB_DIR = $(BIN_DIR)/lib
TEST_DIR = $(PROJ_DIR)/test

LIB_SO = $(LIB_DIR)/libml.so
LIB_A = $(LIB_DIR)/libml_static.a

LIB_FILENAMES = libml knn
LIB_OBJS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(LIB_FILENAMES)))
LIB_C_FILES = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(LIB_FILENAMES)))
LIB_H_FILES = $(addprefix $(INC_DIR)/, $(addsuffix .h, $(LIB_FILENAMES)))

TEST_C_FILES = $(shell find $(TEST_DIR) -type f -name '*.c')
TEST_EXECS = $(TEST_C_FILES:.c=_executable)

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -fstack-protector-all -Werror

all: test lib

test: $(TEST_EXECS)

$(TEST_EXECS): %_executable: %.c $(LIB_SO)
	$(CC) -I$(INC_DIR) -L$(LIB_DIR) -lml $(CFLAGS) -o $@ $<

lib: $(LIB_SO)

$(LIB_SO): $(LIB_OBJS)
	$(CC) -shared -o $(LIB_SO) $(LIB_OBJS)

$(LIB_OBJS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -I$(INC_DIR) $(CFLAGS) -fPIC -c -o $@ $<

clean:
	rm -f $(LIB_SO) $(LIB_OBJS) $(TEST_EXECS)

.PHONY: all test lib clean