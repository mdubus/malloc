CFLAGS = -Wall -Werror -Wextra -Wpadded -fcolor-diagnostics
#CFLAGS=

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CC=clang
#EXEC = libft_malloc_$(HOSTTYPE).so
EXEC = a.out

##### SOURCES #####

SRC_DIR = src
SRC_FILES =	malloc.c search_best_fit.c show_alloc_mem.c ft_print_address.c \
			get_new_arena.c ft_putstr.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

##### OBJECTS #####

OBJ_DIR = obj
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

##### INCLUDES #####

INCL_DIR = includes
INCL_FILES = malloc.h
INCLUDES = -I $(INCL_DIR)/$(INCL_FILES)

##### RULES #####

all: $(EXEC)

$(EXEC): $(OBJS)
	@$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) main.c $(INCLUDES)
#	$(CC) $(CFLAGS) -shared -o $(EXEC) $(OBJS) $(INCLUDES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm $(EXEC)

re: fclean all

.PHONY: all clean fclean re
