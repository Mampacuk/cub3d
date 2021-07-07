NAME = cub3d

MLX = -Lmlx -lmlx -framework OpenGL -framework AppKit -lm
SRCS = $(wildcard *.c)
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
	@${CC} ${OBJS} ${CFLAGS} ${MLX} ./libft/libft.a libmlx.dylib -o ${NAME}
	@echo [cub3d] cub3d successfully compiled. Run ./cub3d \*.cub to read from a map. Provide --save as the second argument for a screenshot.

clean:
	@$(MAKE) -C mlx clean
	@$(MAKE) -C libft fclean
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}
	@${RM} libmlx.dylib
	@${RM} cub3D.bmp

bonus: all

re: fclean all

.PHONY: clean fclean re all