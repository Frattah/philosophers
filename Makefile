# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 10:58:18 by frmonfre          #+#    #+#              #
#    Updated: 2023/05/04 11:41:29 by frmonfre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	philo.c	init.c action.c utils.c

OBJS	=	$(SRCS:.c=.o)

NAME	=	philo

CC		=	gcc

CFLAG	=	-fsanitize=thread -Wall -Werror -Wextra -pthread

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAG) $(OBJS) -o $(NAME)
	norminette

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: re fclean all clean
