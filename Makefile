# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alellouc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/08 18:46:09 by alellouc          #+#    #+#              #
#    Updated: 2021/07/08 20:07:28 by alellouc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ECHO=-echo
CC=-gcc
RM=-rm -rf
CP=-cp
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
CHEADERS=-I .
LDFLAGS=-L ./libft/ -lft 
ALL_FLAGS=$(CFLAGS) $(CHEADERS)
SRC=$(addprefix ft_, $(addsuffix .c, \
	printf\
	set_numeric_ind\
	set_other_ind\
	parse_ind\
	))
OBJ=$(SRC:.c=.o)

.PHONY: clean fclean re all $(LIBFT)

all: $(NAME)

$(NAME): $(LIBFT)
	@$(ECHO) "$(B_GRE)"
	$(CC) $(CHEADERS) $(CFLAGS) -c $(SRC)
	@$(ECHO) "$(B_CYA)"
	$(CP) $(LIBFT_PATH)$(LIBFTA) $@
	$(AR) $@ $(OBJ)
	@$(ECHO) "$(FANCY_RESET)"
	@$(MAKE) clean

$(LIBFT):
	@$(ECHO) "$(B_MAG)"
	$(MAKE) -C $(LIBFT_PATH) all
	@$(ECHO) "$(FANCY_RESET)"

main:
	$(CC) $(CHEADERS) $(CFLAGS) -L. -lftprintf main.c -o test
	./test

clean:
	@$(ECHO) "$(B_RED)"
	$(RM) $(OBJ)
	@$(ECHO) "$(FANCY_RESET)"

libclean: clean
	@$(ECHO) "$(B_RED)"
	$(RM) $(LIBFT_PATH)$(LIBFTA)
	@$(ECHO) "$(FANCY_RESET)"

fclean: libclean
	@$(ECHO) "$(B_RED)"
	$(RM) $(NAME)
	@$(ECHO) "$(FANCY_RESET)"

re: fclean all
