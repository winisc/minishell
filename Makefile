# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wini <wini@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/07 19:14:29 by wini              #+#    #+#              #
#    Updated: 2026/04/25 17:13:32 by wini             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline

SRC_DIR = src
LIBFT_DIR = libs/libft

INCLUDES = -Iincludes -I$(LIBFT_DIR)

SRC = $(SRC_DIR)/main.c \
		$(SRC_DIR)/process_input.c \
		$(SRC_DIR)/signals/treatment_signals.c \
		$(SRC_DIR)/lexer/token.c \
		$(SRC_DIR)/lexer/lexer_utils.c \
		$(SRC_DIR)/lexer/lexer.c

OBJ = $(SRC:.c=.o)

LIBFT_A = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) $(LIBFT_A) $(LDFLAGS) -o $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
