# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/25 00:00:00 by mohamed           #+#    #+#              #
#    Updated: 2026/07/29 13:13:03 by malhassa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I.

SRC_DIR		= srcs
OBJ_DIR		= obj
LIBFT_DIR	= lib/libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a

SRC			= $(SRC_DIR)/main.c \
			  $(SRC_DIR)/game/init.c \
			  $(SRC_DIR)/game/hooks.c \
			  $(SRC_DIR)/game/assets.c \
			  $(SRC_DIR)/game/textures.c \
			  $(SRC_DIR)/raycasting/dda_calculations.c \
			  $(SRC_DIR)/raycasting/game_render.c \
			  $(SRC_DIR)/raycasting/ray_calcuations.c \
			  $(SRC_DIR)/parsing/map_parser.c 

OBJ			= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

MLX_DIR		= minilibx-linux
MLX_LIB		= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
LIBFT_FLAGS	= -L$(LIBFT_DIR) -lft

all: $(NAME)

$(MLX_LIB):
	@make -C $(MLX_DIR) --silent

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR) --silent

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ) $(MLX_LIB) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(MLX_DIR) clean --silent
	@make -C $(LIBFT_DIR) clean --silent
	@echo "object files cleaned"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean --silent
	@echo "full cleanup completed"

re: fclean all

.PHONY: all clean fclean re
