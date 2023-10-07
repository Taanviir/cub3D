# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 19:38:08 by tanas             #+#    #+#              #
#    Updated: 2023/10/07 23:37:29 by sabdelra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
#                                    colors                                    #
# ---------------------------------------------------------------------------- #
GREEN = "\033[1;32m"
RED = "\033[1;3;31m"
BLUE = "\033[3;34m"
YELLOW = "\033[0;33m"
RESET = "\033[0m"
NAME = cub3D
# ---------------------------------------------------------------------------- #
#                                   variables                                  #
# ---------------------------------------------------------------------------- #
CC:= gcc
CFLAGS:= -Wall -Wextra -Werror -O3

UNAME:= $(shell uname)
ifeq ($(UNAME), Linux)
	LIBRARY_FLAGS:= -Lmlx_linux/ -lmlx -lmlx_Linux -Llibft/ -lft -L/usr/lib -lXext -lX11 -lm -lz
	INCLUDES = -Iincludes/ -Ilibft/includes -Imlx_linux/ -I/usr/include
	MLX_DIR:= mlx_linux/
endif
ifeq ($(UNAME), Darwin)
	LIBRARY_FLAGS = -Llibft/ -Lmlx_macos -lmlx -lm -lft -framework OpenGL -framework AppKit
	INCLUDES = -Iincludes/ -Ilibft/includes -Imlx_macos/
	MLX_DIR:= mlx_macos/
	IS_LINUX = 1
endif

TRUE = 1

SRCS_DIR = sources/
SRCS = main.c mlx_core.c utils.c

OBJS_DIR = objects
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

LIBFT = libft/libft.a
MINILIBX = $(MLX_DIR)libmlx.a
# ---------------------------------------------------------------------------- #
#                                    targets                                   #
# ---------------------------------------------------------------------------- #
all : $(NAME)

run : all
	./$(NAME)

$(NAME) : $(LIBFT) $(MINILIBX) $(OBJS)
	$(CC) $(CFLAGS)  $(INCLUDES)  $(OBJS) -o $(NAME) $(LIBRARY_FLAGS)
	@echo $(GREEN)"cub3D ready for play."$(RESET)

$(OBJS_DIR)/%.o : $(SRCS_DIR)%.c | $(OBJS_DIR)
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
	@if [ $(UNAME) == Darwin ]; then \
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
	@if [ $(UNAME) == Darwin ]; then \
		rm -f libmlx.dylib; \
	fi
	@make fclean -sC libft
	@echo $(RED)"Removing $(NAME), libft.a and libmlx.a\n"$(RESET)

re : fclean all

.PHONY = all clean fclean re
