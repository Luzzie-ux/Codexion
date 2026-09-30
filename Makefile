# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rodrpere <rodrpere@42.student.porto.c      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/24 11:03:24 by rodrpere          #+#    #+#              #
#    Updated: 2026/09/30 01:10:17 by rodrpere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ELF:
NAME=codexion

# Compiling:
CC=cc
CFLAGS= -Wall -Wextra -Werror -pthread
INCS=-Iincs

# Files:
MAIN=main.c
ENV=srcs/env
RUNTIME=srcs/runtime
UTILS=srcs/utils

BUILD=build
SRCS=$(UTILS)/errors.c $(UTILS)/memory.c $(UTILS)/strings.c \
	 $(ENV)/coder.c $(ENV)/dongle.c $(ENV)/table.c \
	 $(RUNTIME)/parser.c $(RUNTIME)/scheduler.c $(RUNTIME)/simulation.c \
	 $(MAIN)
OBJS=$(patsubst %.c,$(BUILD)/%.o,$(SRCS))

all: banner $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCS) -o $(NAME) $(OBJS)

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	rm -rf $(BUILD)/main.o
	rm -rf $(BUILD)/srcs

fclean: clean
	rm -rf $(NAME)

re: banner fclean $(NAME)

debug: CFLAGS += -g
debug: re
	@echo "[You can now run $(NAME) with GDB/Valgrind]"

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
