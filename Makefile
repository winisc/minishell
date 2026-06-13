# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wini <wini@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/07 19:14:29 by wini              #+#    #+#              #
#    Updated: 2026/06/08 23:51:15 by wini             ###   ########.fr        #
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
		$(SRC_DIR)/lexer/lexer.c \
		$(SRC_DIR)/env/env_init.c \
		$(SRC_DIR)/env/env_utils.c \
		$(SRC_DIR)/parser/parser.c \
		$(SRC_DIR)/parser/parser_syntax.c \
		$(SRC_DIR)/parser/parser_utils.c \
		$(SRC_DIR)/parser/parser_redir.c \
		$(SRC_DIR)/expansion/expand.c \
		$(SRC_DIR)/expansion/expand_quote.c \
		$(SRC_DIR)/expansion/expand_dollar.c \
		$(SRC_DIR)/expansion/expand_utils.c \
		$(SRC_DIR)/expansion/expand_split.c \
		$(SRC_DIR)/expansion/expand_fields.c \
		$(SRC_DIR)/env/env_array.c \
		$(SRC_DIR)/env/env_modify.c \
		$(SRC_DIR)/utils/utils.c \
		$(SRC_DIR)/execution/path.c \
		$(SRC_DIR)/execution/exec.c \
		$(SRC_DIR)/execution/exec_child.c \
		$(SRC_DIR)/execution/exec_utils.c \
		$(SRC_DIR)/redirections/redir.c \
		$(SRC_DIR)/redirections/heredoc.c \
		$(SRC_DIR)/redirections/heredoc_utils.c \
		$(SRC_DIR)/builtins/echo.c \
		$(SRC_DIR)/builtins/pwd_env.c \
		$(SRC_DIR)/builtins/cd.c \
		$(SRC_DIR)/builtins/export.c \
		$(SRC_DIR)/builtins/unset.c \
		$(SRC_DIR)/builtins/exit.c \
		$(SRC_DIR)/builtins/builtin_dispatch.c

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
