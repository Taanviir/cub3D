# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tanas <tanas@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 19:38:08 by tanas             #+#    #+#              #
#    Updated: 2023/09/07 19:38:09 by tanas            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
C_FLAGS = -Wall -Wextra -Werror -O3
LIBRARY_FLAGS = -lmlx -lm -lft -Llibft/ -Lmlx-macos/ -framework OpenGL -framework AppKit
INCLUDES = -Iincludes/ -Ilibft/includes -Imlx-macos/
HEADERS = includes/cub3D.h

SRCS_DIR = sources/
SRCS_LIST = main.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_DIR = objects/
OBJS_LIST = $(SRCS_LIST:.c=.o)
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_LIST))

LIBFT = libft/libft.a
MINILIBX = mlx-macos/libmlx.a

# colours
GREEN = "\033[1;32m"
RED = "\033[1;3;31m"
BLUE = "\033[3;34m"
YELLOW = "\033[0;33m"
RESET = "\033[0m"

all : $(NAME)

$(NAME) : $(LIBFT) $(MINILIBX) $(OBJS)
	@cc $(C_FLAGS) $(LIBRARY_FLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
	@echo $(GREEN)"cub3D ready for play."$(RESET)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(HEADERS)
	@mkdir -p $(OBJS_DIR)
	@cc $(C_FLAGS) -c $(INCLUDES) $< -o $@
	@echo $(BLUE)"Compiling $<."$(RESET)

$(LIBFT) :
	@echo $(YELLOW)"Creating $(LIBFT)"$(RESET)
	@make -sC libft
	@echo $(GREEN)"\nLibft is ready. ✅\n"$(RESET)

$(MINILIBX) :
	@echo $(YELLOW)"Creating $(MINILIBX)"$(RESET)
	@make -sC mlx-macos
	@echo $(GREEN)"MLX Library is ready. ✅\n"$(RESET)

clean :
	@make clean -sC libft
	@make clean -sC mlx-macos
	@rm -rf $(OBJS_DIR)
	@echo $(RED)"\nRemoving object directory and files"$(RESET)

fclean : clean
	@rm -f $(NAME)
	@make fclean -sC libft
	@echo $(RED)"Removing $(NAME), libft.a and libmlx.a\n"$(RESET)

re : fclean all

.PHONY = all clean fclean re