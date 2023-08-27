NAME = cub3d

CC = gcc

FLAGS = -Wall -Werror -Wextra #-g -fsanitize=address

INCL = -I ./includes/\
       -I ./minilibx-linux/\
       -I ./libft/

SRCDIR = ./srcs/
SRC = main.c\
      parse.c\
      debug.c\
	  checkers.c\
	  vector.c\
	  image.c\
	  raycast.c\
	  raycast_draw.c\
	  key_hooks.c\
	  movement.c\
	  movement_utils.c\
	  render.c\
	  depth_buffer.c\
	  door.c\
	  minimap.c
SRCS = $(addprefix $(SRCDIR), $(SRC))

OBJDIR = ./objects/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJDIR), $(OBJ))

# Minilibx 
MLX_PATH = minilibx-linux/
MLX_NAME = libmlx.a
MLX = $(MLX_PATH)$(MLX_NAME)

# Libft
LIBFT_PATH = libft/
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_PATH)$(LIBFT_NAME)

# Colours
GREEN = \e[0;32m
YELLOW = \e[0;33m
CYAN = \e[0;36m
RESET = \e[0m

all : $(OBJDIR) $(MLX) $(LIBFT) $(NAME)
	@printf "$(GREEN) | Cub3d executable created $(RESET)\n"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@$(CC) $(FLAGS) -c $< -o $@ $(INCL)

$(NAME) : $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $@ $(INCL) $(LIBFT) $(MLX) -lXext -lX11 -lm
	@printf "$(YELLOW) | Compiling... $(RESET)\n"

$(LIBFT):
	@make -sC $(LIBFT_PATH)

$(MLX):
	@make -sC $(MLX_PATH)

clean :
	@rm -rf $(OBJDIR)
	@make -C $(LIBFT_PATH) clean
	@make -C $(MLX_PATH) clean
	@printf "$(CYAN) | Cleaned objects $(RESET)\n"

fclean : clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean
	@printf "$(CYAN) | Cleaned executable $(RESET)\n"

re : fclean all

.PHONY : all clean fclean re
