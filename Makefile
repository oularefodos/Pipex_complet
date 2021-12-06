# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: foulare <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/06 14:35:42 by foulare           #+#    #+#              #
#    Updated: 2021/12/06 17:36:26 by foulare          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= pipex

NAME_B= pipex_bonus

INCLUDE= pipex.h

INCLUDE_B= pipex_bonus.h

SRCS= ft_perror.c  ft_split.c   ft_strjoin.c ft_strncmp.c  pipex.c

SRCS_B= ft_perror_bonus.c     ft_strjoin_bonus.c    get_next_line.c  here_doc_bonus.c \
	   ft_split_bonus.c      ft_strncmp_bonus.c    get_next_line_utils.c pipex_bonus.c

CFLAGS= -Wall -Wextra -Werror

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(SRCS) $(INCLUDE)
	gcc $(CFLAGS) $(SRCS) -I $(INCLUDE) -o $(NAME)

bonus: $(SRCS_B) $(INCLUDE_B)
	gcc $(CFLAGS) $(SRCS_B) -I $(INCLUDE_B) -o $(NAME_B)

clean:
	rm -f $(NAME) $(NAME_B)

fclean: clean
re: fclean all bonus
