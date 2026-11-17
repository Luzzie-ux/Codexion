# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rodrpere <rodrpere@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/11/16 17:46:16 by rodrpere          #+#    #+#              #
#    Updated: 2026/11/17 18:53:53 by rodrpere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ELF:
NAME=codexion

# Compiling:
CC=cc
CFLAGS= -Wall -Wextra -Werror -pthread
INCS=-Iincs

# Programs:
COMPDB=compiledb
FORMATTER=c_formatter_42
LINTER=norminette

# Files:
HEADER=codexion.h
BUILD=build

MAIN	=   srcs/main.c
OBJECTS =   srcs/objects/coder.c \
			srcs/objects/config.c \
			srcs/objects/dongle.c \
			srcs/objects/table.c
METHODS =   srcs/methods/coder.c \
			srcs/methods/dongle.c \
			srcs/methods/pair.c \
			srcs/methods/heap.c \
			srcs/methods/table.c
ROUTINE =   srcs/routine/monitor.c \
			srcs/routine/routine.c \
			srcs/routine/utils.c \
			srcs/routine/helpers.c

SRCS = $(OBJECTS) $(STRTOL10) $(METHODS) $(ROUTINE) $(MAIN)
OBJS = $(patsubst %.c,$(BUILD)/%.o,$(SRCS))

# Rules:
all: banner $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCS) -o $(NAME) $(OBJS)

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	rm -rf $(BUILD)/srcs

fclean: clean
	rm -rf $(NAME)

re: banner fclean $(NAME)

debug: CFLAGS += -g
debug: re
	@echo "[You can now run $(NAME) with GDB/Valgrind]"

compdb:
	$(COMPDB) -o build/compile_commands.json make re

format:
	$(FORMATTER) $(SRCS) incs/$(HEADER)

lint:
	$(LINTER) $(SRCS) incs/$(HEADER)

banner:
	@echo " ▓▓▓   ▓▓▓  ▓▓▓▓  ▓▓▓▓▓ ▓   ▓ ▓▓▓  ▓▓▓  ▓   ▓   "
	@echo "▓ ░░░ ▓ ░░▓ ▓░░░▓ ▓░░░░░ ▓ ▓ ░ ▓░░▓ ░░▓ ▓▓  ▓░  "
	@echo "▓░ ░░░▓░ ░▓░▓░░░▓░▓▓▓▓░░░ ▓ ░ ░▓░░▓░ ░▓░▓░▓ ▓░░ "
	@echo "▓░░   ▓░░ ▓░▓░░ ▓░▓░░░░  ▓ ▓ ░ ▓░░▓░░ ▓░▓░░▓▓░░ "
	@echo " ▓▓▓   ▓▓▓ ░▓▓▓▓ ░▓▓▓▓▓░▓ ░ ▓ ▓▓▓░ ▓▓▓ ░▓░░ ▓░░ "
	@echo "  ░░░   ░░░ ░░░░░ ░░░░░░ ░ ░ ░ ░░░  ░░░ ░░░  ░░ "
	@echo "   ░░░   ░░░  ░░░░  ░░░░░ ░   ░ ░░░  ░░░  ░   ░ "
	@echo ""

.PHONY: all clean fclean re debug compdb format lint banner
