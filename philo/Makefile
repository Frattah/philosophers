# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 10:58:18 by frmonfre          #+#    #+#              #
#    Updated: 2023/05/22 11:40:41 by frmonfre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	philo.c	init.c action.c utils.c	routine.c

OBJS	=	$(SRCS:.c=.o)

NAME	=	philo

CC	=	gcc

CFLAG	=	-Wall -Werror -Wextra -pthread

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAG) $(OBJS) -o $(NAME)
	norminette
	@echo "______ _     _ _                       _                   "
	@echo "| ___ \ |   (_) |                     | |                  "
	@echo "| |_/ / |__  _| | ___  ___  ___  _ __ | |__   ___ _ __ ___ "
	@echo "|  __/| '_ \| | |/ _ \/ __|/ _ \| '_ \| '_ \ / _ \ '__/ __|"
	@echo "| |   | | | | | | (_) \__ \ (_) | |_) | | | |  __/ |  \__ \\"
	@echo "\_|   |_| |_|_|_|\___/|___/\___/| .__/|_| |_|\___|_|  |___/"
	@echo "                                | |                        "
	@echo "                                |_|                        \n"

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

push: fclean
	git add .
	git commit -m "Makefile auto-commit"
	git push

.PHONY: re fclean all clean
