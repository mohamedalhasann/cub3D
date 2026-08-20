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
CFLAGS		= -Wall -Wextra -Werror -I. -IMLX42/include

SRC_DIR		= srcs
OBJ_DIR		= obj
LIBFT_DIR	= lib/libft
GNL_DIR		= lib/gnl
LIBFT_LIB	= $(LIBFT_DIR)/libft.a

SRC			= $(SRC_DIR)/main.c \
			  $(SRC_DIR)/game/init.c \
			  $(SRC_DIR)/game/hooks.c \
			  $(SRC_DIR)/game/assets.c \
			  $(SRC_DIR)/game/textures.c \
			  $(SRC_DIR)/raycasting/dda_calculations.c \
			  $(SRC_DIR)/raycasting/game_render.c \
			  $(SRC_DIR)/raycasting/ray_calcuations.c \
			  $(SRC_DIR)/parsing/checker.c \
			  $(SRC_DIR)/parsing/get_values.c \
			  $(SRC_DIR)/parsing/parse_player.c \
			  $(SRC_DIR)/parsing/validate_map.c

GNL_SRC		= $(GNL_DIR)/srcs/get_next_line.c \
			  $(GNL_DIR)/srcs/get_next_line_utils.c

OBJ			= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
GNL_OBJ		= $(patsubst $(GNL_DIR)/srcs/%.c,$(OBJ_DIR)/gnl/%.o,$(GNL_SRC))

MLX_DIR		= MLX42
MLX_BUILD	= $(MLX_DIR)/build
MLX_LIB		= $(MLX_BUILD)/libmlx42.a
MLX_FLAGS	= -L$(MLX_BUILD) -lmlx42 -lglfw -ldl -lGL -pthread -lm
LIBFT_FLAGS	= -L$(LIBFT_DIR) -lft
CFLAGS		+= -I$(GNL_DIR)/srcs

all: $(NAME)

$(MLX_LIB):
	@cmake -S $(MLX_DIR) -B $(MLX_BUILD) -DGLFW_FETCH=OFF
	@cmake --build $(MLX_BUILD) --parallel

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR) --silent

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/gnl/%.o: $(GNL_DIR)/srcs/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ) $(GNL_OBJ) $(MLX_LIB) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(GNL_OBJ) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean --silent
	@echo "object files cleaned"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean --silent
	@echo "full cleanup completed"

re: fclean all

.PHONY: all clean fclean re

