# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtani <mtani@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 17:17:07 by mtani             #+#    #+#              #
#    Updated: 2024/01/16 15:02:28 by mtani            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = ./mandatory/pipex.c ./mandatory/pipex_utils.c ./mandatory/ft_altsplit.c ./mandatory/ft_find_functions.c ./mandatory/ft_free_all.c

BSRCS = ./bonus/pipex_bonus.c ./bonus/pipex_utils_bonus.c ./bonus/ft_split_bonus.c ./bonus/ft_altsplit_bonus.c ./bonus/ft_find_functions_bonus.c ./bonus/ft_free_all_bonus.c ./bonus/get_next_line_bonus.c \
	./bonus/get_next_line_utils_bonus.c ./bonus/ft_here_doc_bonus.c ./bonus/ft_init_dups_bonus.c

OBJS = $(SRCS:.c=.o)

BOBJS = $(BSRCS:.c=.o)

all: $(NAME)

bonus: $(BOBJS)
	cc -Wall -Wextra -Werror $(BOBJS) -o $(NAME)
	
$(NAME): $(OBJS)
	cc -g -Wall -Wextra -Werror $(OBJS) -o $(NAME)

%.o: %.c
	cc -Wall -Wextra -Werror -g -c $< -o $@

clean:
	rm -f $(OBJS) $(BOBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
