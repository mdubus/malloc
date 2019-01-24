#CFLAGS = -Wall -Werror -Wextra -Wpadded -g -Weverything -fcolor-diagnostics -fsanitize=address
CFLAGS=

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CC=clang
EXEC = libft_malloc_$(HOSTTYPE).so

##### SOURCES #####

SRC_DIR = src
SRC_FILES = malloc.c
SRCS = $(SRC_DIR)/$(SRC_FILES)

##### OBJECTS #####

OBJ_DIR = obj
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(OBJ_DIR)/$(OBJ_FILES)

##### INCLUDES #####

INCL_DIR = includes
INCL_FILES = malloc.h
INCLUDES = -I $(INCL_DIR)/$(INCL_FILES)

##### RULES #####

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -shared -o $(EXEC) $(OBJS) $(INCLUDES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm $(EXEC)

re: fclean all
