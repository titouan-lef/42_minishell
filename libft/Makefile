# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/25 22:29:47 by tle-floc          #+#    #+#              #
#    Updated: 2025/01/17 15:09:58 by tle-floc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#===================== BASE =====================#

CC :=			cc

CFLAGS +=		-Wall -Wextra -Werror -MP -MMD

MAKEFLAGS +=	--no-print-directory

BUILD_DIR :=	.build/

NAME :=			libft.a

#==================== COLOR =====================#

INIT :=		\e[0m
BLACK :=	\e[30m
RED :=		\e[31m
GREEN :=	\e[32m
YELLOW :=	\e[33m
BLUE :=		\e[34m
MAGENTA :=	\e[35m
CYAN :=		\e[36m

#==================== SOURCE ====================#

SRC_DIR =	src/

SRC =		char/ft_check_alnum.c \
			char/ft_check_char.c \
			collection/list/ft_lst_add.c \
			collection/list/ft_lst_change.c \
			collection/list/ft_lst_del.c \
			collection/list/ft_lst_primitive.c \
			compare/ft_compare.c \
			compare/ft_strcompare.c \
			convert/ft_convert_char.c \
			convert/ft_convert_int.c \
			convert/ft_convert_str.c \
			copy/ft_copy.c \
			copy/ft_strcopy.c \
			get_next_line/get_next_line.c \
			malloc/ft_calloc.c \
			malloc/ft_free.c \
			print/printnumber/ft_printnumber.c \
			print/printnumber/ft_printnumber_base.c \
			print/printnumber/ft_printunsignednumber.c \
			print/printnumber/ft_printunsignednumber_base.c \
			print/printstr/ft_printendl.c \
			print/printstr/ft_printstr.c \
			print/ft_printchar.c \
			printf/ft_printf.c \
			printf/ft_printf_text.c \
			printf/ft_printf_number.c \
			printf/ft_printf_address.c \
			search/ft_search.c \
			search/ft_strsearch.c \
			sort/ft_simplesort.c \
			sort/ft_simplesort_custom.c \
			string/ft_change_str.c \
			string/ft_concat.c \
			string/ft_get_substr.c \
			string/ft_split.c \
			string/ft_split_charset.c \
			string/ft_strlen.c \
			ft_fill_memory.c

#==================== OBJECT ====================#

OBJ :=		$(SRC:%.c=$(BUILD_DIR)%.o)

OBJ_DIR :=	$(sort $(shell dirname $(OBJ)))

#================== DEPENDENCY ==================#

DEP :=		$(SRC:%.c=$(BUILD_DIR)%.d)

#==================== HEADER ====================#

HEADERS =	./include/

#===================== RULE =====================#

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(CYAN)Archiving : $(MAGENTA)$@$(INIT)"
	@ar -rcs $@ $^

$(BUILD_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@echo "$(GREEN)Compiling : $(MAGENTA)$<$(INIT)"
	@$(CC) $(CFLAGS) -I$(HEADERS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@if [ -d $(BUILD_DIR) ]; then echo "$(RED)Removing directory : $(BLUE)$(BUILD_DIR)$(INIT)"; rm -rf $(BUILD_DIR); fi;

fclean: clean
	@if [ -f $(NAME) ]; then echo "$(RED)Removing : $(MAGENTA)$(NAME)$(INIT)"; rm -f $(NAME); fi;

re:	fclean all

.PHONY: all clean fclean re

-include $(DEP)