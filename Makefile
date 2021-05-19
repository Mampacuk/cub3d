NAME = cub3d

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)libft.a
LIBMLX_DIR = ./mlx
LIBMLX = $(LIBMLX_DIR)libmlx.dylib
MAKE = make
CLEAN = clean
FCLEAN = fclean
SRC = ft_createbmp.c ft_parser_utils1.c ft_parser_utils2.c ft_parser_utils3.c ft_parser_utils4.c ft_parser.c ft_raycast_utils1.c ft_raycast_utils2.c ft_raycast.c ft_quicksort.c get_next_line.c mlx_utils.c cub3d.c cub3d_utils.c ft_check.c
OBJ = $(SRC:.c=.o)
CC = gcc
FLAG = -Wall -Werror -Wextra -g -O3
FLAGMLX = -framework OpenGL -framework AppKit
OPTION = -c -D GL_SILENCE_DEPRECATION
OPTIONOBJ = -o
DEL = rm -rf

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(LIBMLX)
	@echo [cub3d] Compiling Libft...
	@cd $(LIBFT_DIR) && mv ./libft.a ../
	@echo [cub3d] Compiling mlx...
	@cd $(LIBMLX_DIR) && mv ./libmlx.dylib ../
	@echo [cub3d] Compiling cub3d...
	@$(CC) $(FLAG) $(OBJ) -L. -lmlx -lft $(FLAGSMLX) $(OPTIONOBJ) $(NAME)
	@echo [cub3d] cub3d successfully compiled. Run ./cub3d \*.cub to read from a map. Provide --save as the second argument for a screenshot.

$(LIBFT):
	@cd $(LIBFT_DIR) && $(MAKE)

$(LIBMLX):
	@cd $(LIBMLX_DIR) && $(MAKE)

%.o: %.c
	@$(CC) $(FLAG) $(OPTION) $< $(OPTIONOBJ) $@

clean:
	@$(DEL) $(OBJ)
	@cd $(LIBFT_DIR) && $(MAKE) $(CLEAN)
	@cd $(LIBMLX_DIR) && $(MAKE) $(CLEAN)
	
fclean: clean
	@$(DEL) $(NAME) ./libft.a ./libmlx.dylib
	@$(DEL) $(OBJ)
	@cd $(LIBFT_DIR) && $(MAKE) $(FCLEAN)
	
re: fclean all

.PHONY: all clean bonus fclean re