# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 19:38:08 by tanas             #+#    #+#              #
#    Updated: 2023/11/17 05:14:23 by sabdelra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------- colors ---------------------------------- #
GREEN := "\033[1;32m"
RED := "\033[1;3;31m"
BLUE := "\033[3;34m"
YELLOW := "\033[0;33m"
RESET := "\033[0m"

# --------------------------------- variables -------------------------------- #
NAME := cub3D
CFLAGS := -Wall -Wextra -Werror
UNAME := $(shell uname)
LIBRARY_FLAGS := -Llibft/ -lft -lm -lz -lmlx -Llibft/
INCLUDES := -Iincludes/ -Ilibft/includes

ifeq ($(UNAME), Linux)
	LIBRARY_FLAGS += -Lmlx_linux/ -lmlx_Linux -L/usr/lib -lXext -lX11
	INCLUDES += -Imlx_linux/ -I/usr/include -D__LINUX__
	MLX_DIR := mlx_linux/
else ifeq ($(UNAME), Darwin)
	LIBRARY_FLAGS += -Lmlx_macos/ -framework OpenGL -framework AppKit
	INCLUDES += -Imlx_macos/
	MLX_DIR := mlx_macos/
endif

SRCS_DIR = sources
SRCS = main.c mlx_core.c utils.c map.c grid_validate.c events.c \
	draw_pixel.c ray_caster.c

OBJS_DIR = objects
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

LIBFT = libft/libft.a
MINILIBX = $(MLX_DIR)libmlx.a

MAP:= ./test_maps/wolf.cub

# ---------------------------------- targets --------------------------------- #
all : $(NAME)

run : all
	./$(NAME) $(MAP)

# --------------------------------- debugging -------------------------------- #

valgrind: CFLAGS += -DDEBUG -ggdb3
valgrind: re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME) $(MAP)

sanitize: CFLAGS += -fsanitize=address -ggdb3
sanitize: re

debug: CFLAGS += -ggdb3
debug: re
	./$(NAME) $(MAP)

$(NAME) : $(LIBFT) $(MINILIBX) $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(LIBRARY_FLAGS)
	@echo $(GREEN)"cub3D ready for play."$(RESET)

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
	@echo $(BLUE)"Compiling $<."$(RESET)

$(OBJS_DIR) :
	@mkdir -p $(OBJS_DIR)

$(LIBFT) :
	@echo $(YELLOW)"Creating $(LIBFT)"$(RESET)
	@make -sC libft
	@echo $(GREEN)"\nLibft is ready. ✅\n"$(RESET)

$(MINILIBX) :
	@echo $(YELLOW)"Creating $(MINILIBX)"$(RESET)
	@make -sC $(MLX_DIR)
	@if [ $(UNAME) = Darwin ]; then \
		cp $(MLX_DIR)libmlx.dylib ./ ; \
	fi
	@echo $(GREEN)"MLX Library is ready. ✅\n"$(RESET)

clean :
	@make clean -sC libft
	@make clean -sC $(MLX_DIR)
	@rm -rf $(OBJS_DIR)
	@echo $(RED)"\nRemoving object directory and files"$(RESET)

fclean : clean
	@rm -f $(NAME)
	@if [ $(UNAME) = Darwin ]; then \
		rm -f libmlx.dylib; \
	fi
	@make fclean -sC libft
	@echo $(RED)"Removing $(NAME), libft.a and libmlx.a\n"$(RESET)

re : fclean all

.PHONY = all clean fclean re
