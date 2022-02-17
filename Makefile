# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/30 17:02:06 by ynakashi          #+#    #+#              #
#    Updated: 2022/01/31 12:02:16 by ynakashi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	fractol

CC		=	gcc

RM		=	rm -rf

CFLAGS	=	-Wall -Wextra -Werror

MLX_FLAGS	=	-L/usr/X11/include/../lib -lXext -lX11 -lm

NO_BUILTIN_FLAGS	=	-fno-builtin

SRCS	=	./srcs/main.c\
			./srcs/calculate.c\
			./srcs/destroy.c\
			./srcs/draw.c\
			./srcs/ft_atof.c\
			./srcs/hook.c\
			./srcs/init.c

OBJS	=	$(SRCS:.c=.o)

LIBFT_PATH	=	./libft/
LIBFT_OBJS	=	$(LIBFT_PATH)*.o
LIBFT_ARC	=	$(LIBFT_PATH)*.a
LIBFT_MAKE	=	make -C $(LIBFT_PATH)

MLX_PATH	=	./minilibx-linux/
MLX_OBJS	=	$(MLX_PATH)*.o
MLX_ARC		=	$(MLX_PATH)*.a
MLX_MAKE	=	make -C $(MLX_PATH)

# suffix rule
# make -p で暗黙のルールが見れる
# explicitly add a flag when creating object files
#$< 最初の依存するファイルの名前 -> 元になるファイル
#$@ ターゲットファイル名 -> 作りたいファイル
#echo $<
#echo $@
.c.o	:
	$(CC) $(CFLAGS) -c $< -o $@
# もしくは
#$(OBJS)	: $(SRCS)
#	$(CC) $(CFLAGS) -c $(SRCS)

$(NAME)	: $(OBJS)
	$(LIBFT_MAKE)
	$(MLX_MAKE)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_ARC) $(MLX_ARC) $(MLX_FLAGS) -o $(NAME)

all		: $(NAME)

clean	:
	$(RM) $(OBJS) $(LIBFT_OBJS) $(MLX_OBJS)

fclean	: clean
	$(RM) $(NAME) $(LIBFT_ARC) $(MLX_ARC)

re		: fclean all

bonus	: $(NAME)

nm		: fclean $(OBJS)
	$(LIBFT_MAKE)
	$(MLX_MAKE)
	$(CC) $(CFLAGS) $(NO_BUILTIN_FLAGS) $(OBJS) $(LIBFT_ARC) $(MLX_ARC) $(MLX_FLAGS) -o $(NAME)
	nm -u $(NAME) \
		| grep -E "^_" | grep -E "^_X" -v | grep -E "^__" -v | cut -b 2- \
		| grep -E '^(open|close|read|write|printf|malloc|free|perror|strerror|exit|cos|sin|tan|asin|acos|atan2|log|pow|fmod|floor|ceil|fmin|fabs)' -v

.PHONY	: all clean fclean re bonus nm
