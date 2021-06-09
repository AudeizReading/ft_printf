# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alellouc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/08 18:46:09 by alellouc          #+#    #+#              #
#    Updated: 2021/06/09 09:56:01 by alellouc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ECHO=-echo
CC=-gcc
RM=-rm -rf
AR=-ar rcs
MAKE=-make
B_RED=\033[1;31m
B_GRE=\033[1;32m
B_YEL=\033[1;33m
B_BLU=\033[1;34m
B_MAG=\033[1;35m
B_CYA=\033[1;36m
FANCY_RESET=\033[0m
NAME=libftprintf.a
LIBFT=libft
LIBFTA=libft.a
LIBFT_PATH=./libft/
CFLAGS=-Wall -Wextra -Werror
CHEADERS=-I.
LDFLAGS=-L ./libft/ -lftprintf
ALL_FLAGS=$(CFLAGS) $(CHEADERS)
SRC=$(addprefix ft_, $(addsuffix .c, \
	printf\
	))
OBJ=$(SRC:.c=.o)

.PHONY: clean fclean re all $(LIBFT)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) $(LIBFT)
	$(AR) $@ $(OBJ)
	$(MAKE) clean

test: $(OBJ)
	$(ECHO) $(OBJ)

%.o:%.c
	$(CC) $(ALL_FLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH) all

clean:
	@$(ECHO) "$(B_RED)"
	$(RM) $(OBJ)
	@$(ECHO) "$(FANCY_RESET)"

libclean: clean
	$(RM) $(LIBFT)/$(LIBFTA)

fclean: libclean
	$(RM) $(NAME)

re: fclean all
