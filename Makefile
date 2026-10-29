# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marcunix <marcunix@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/24 11:03:24 by rodrpere          #+#    #+#              #
#    Updated: 2026/10/29 13:44:49 by rodrpere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ELF:
NAME=codexion

# Compiling:
CC=cc
CFLAGS= -Wall -Wextra -Werror -pthread
INCS=-Iincs

# Files:
BUILD=build

SRCS=srcs/main.c \
	srcs/ctor/signal.c \
	srcs/ctor/config.c \
	srcs/ctor/dongle.c \
	srcs/ctor/coder.c \
	srcs/ctor/table.c \
	srcs/ctor/waiter.c
OBJS=$(patsubst %.c,$(BUILD)/%.o,$(SRCS))

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
	compiledb -o build/compile_commands.json make re

banner:
	@echo " ▓▓▓   ▓▓▓  ▓▓▓▓  ▓▓▓▓▓ ▓   ▓ ▓▓▓  ▓▓▓  ▓   ▓   "
	@echo "▓ ░░░ ▓ ░░▓ ▓░░░▓ ▓░░░░░ ▓ ▓ ░ ▓░░▓ ░░▓ ▓▓  ▓░  "
	@echo "▓░ ░░░▓░ ░▓░▓░░░▓░▓▓▓▓░░░ ▓ ░ ░▓░░▓░ ░▓░▓░▓ ▓░░ "
	@echo "▓░░   ▓░░ ▓░▓░░ ▓░▓░░░░  ▓ ▓ ░ ▓░░▓░░ ▓░▓░░▓▓░░ "
	@echo " ▓▓▓   ▓▓▓ ░▓▓▓▓ ░▓▓▓▓▓░▓ ░ ▓ ▓▓▓░ ▓▓▓ ░▓░░ ▓░░ "
	@echo "  ░░░   ░░░ ░░░░░ ░░░░░░ ░ ░ ░ ░░░  ░░░ ░░░  ░░ "
	@echo "   ░░░   ░░░  ░░░░  ░░░░░ ░   ░ ░░░  ░░░  ░   ░ "
	@echo ""

.PHONY: all clean fclean re debug compdb banner
