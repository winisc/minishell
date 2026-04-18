# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wsilveir <wsilveir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/07 19:14:29 by wini              #+#    #+#              #
#    Updated: 2026/03/15 18:37:11 by wsilveir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src
LIBFT_DIR = libs/libft
FT_PRINTF_DIR = libs/ft_printf

INCLUDES = -Iincludes -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR)

SRC = $(SRC_DIR)/main.c

OBJ = $(SRC:.c=.o)

LIBFT_A = $(LIBFT_DIR)/libft.a
FT_PRINTF_A = $(FT_PRINTF_DIR)/libftprintf.a

all: libft ft_printf $(NAME)

$(NAME): $(OBJ) $(LIBFT_A) $(FT_PRINTF_A)
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) $(LIBFT_A) $(FT_PRINTF_A) -o $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

libft:
	@$(MAKE) -C $(LIBFT_DIR)

ft_printf:
	@$(MAKE) -C $(FT_PRINTF_DIR)

clean:
	rm -f $(OBJ)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(FT_PRINTF_DIR)

fclean: clean
	rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@$(MAKE) fclean -C $(FT_PRINTF_DIR)

re: fclean all

.PHONY: all clean fclean re libft ft_printf
