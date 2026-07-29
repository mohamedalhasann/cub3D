# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/25 00:00:00 by mohamed           #+#    #+#              #
#    Updated: 2026/07/29 14:03:19 by malhassa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I.

SRC_DIR		= srcs
OBJ_DIR		= obj

SRC			= $(SRC_DIR)

OBJ			= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

MLX_DIR		= minilibx-linux
MLX_LIB		= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

all: $(NAME)

$(MLX_LIB):
	@make -C $(MLX_DIR) --silent

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(MLX_DIR) clean --silent
	@echo "object files cleaned."

fclean: clean
	@rm -f $(NAME)
	@echo "full cleanup completed."

re: fclean all

.PHONY: all clean fclean re
