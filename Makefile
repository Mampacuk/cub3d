NAME = cub3d

MLX = -Lmlx -lmlx -framework OpenGL -framework AppKit -lm
SRCS = ft_createbmp.c ft_parser_utils1.c ft_parser_utils2.c ft_parser_utils3.c ft_parser_utils4.c ft_parser.c ft_raycast_utils1.c ft_raycast_utils2.c ft_raycast.c ft_quicksort.c get_next_line.c mlx_utils.c cub3d.c cub3d_utils.c ft_check.c
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = -O3 -Wall -Wextra -Werror
RM = rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	@echo [cub3d] Compiling mlx...
	@$(MAKE) -C ./mlx
	@echo [cub3d] Compiling Libft...
	@$(MAKE) -C ./libft
	@mv mlx/libmlx.dylib .
	@echo [cub3d] Compiling cub3D...
	@${CC} ${OBJS} ${CFLAGS} ${MLX} ./libft/libft.a -o ${NAME}
	@echo [cub3d] cub3d successfully compiled. Run ./cub3d \*.cub to read from a map. Provide --save as the second argument for a screenshot.

clean:
	@$(MAKE) -C mlx clean
	@$(MAKE) -C libft fclean
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}
	@${RM} libmlx.dylib
	@${RM} cub3D.bmp

re: fclean all

.PHONY: clean fclean re all