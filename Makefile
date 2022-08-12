NAME	=	philo
HEADER	=	philo.h
GCC		=	gcc -g -Wall -Wextra -Werror

SRCS	=	main.c utils.c printer.c ft_atoi.c monitor.c p_eat.c initial_param.c ft_free.c

OBJ		=	$(SRCS:.c=.o)

all		:	$(NAME)

%.o		:	%.c $(HEADER)
	$(GCC) $< -c

$(NAME)	:	$(OBJ) $(HEADER)
	$(GCC) -o $(NAME) $(OBJ)

clean	:
	rm -f $(OBJ)

fclean	:	clean
	rm -f $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re
