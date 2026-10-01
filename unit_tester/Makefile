# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/15 14:44:24 by lguerbig          #+#    #+#              #
#    Updated: 2025/02/04 12:03:13 by tle-floc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#===================== BASE =====================#

CC				:=	cc
CFLAGS			+=	-Wall -Wextra -Werror -MP -MMD -g
MAKEFLAGS		+=	--no-print-directory
BUILD_DIR		:=	.build/
LIBFT_DIR		:=	../minishell/libft/include
HEADERS			:=	../minishell/include/
NAME			:=	minishell_unit_tester

#==================== SOURCE ====================#

SRC				=	unit_test/unit_test.c		\
					tester.c					\
					test_cd.c					\
					test_echo.c					\
					test_pwd.c					\
					test_unset.c				\
					test_tokenizer.c			\
					test_lexer.c				\
					test_tree.c					\
					test_get_tree.c				\
					test_var_expansion.c		\
					test_exit_expansion.c		\
					test_tilde_expansion.c		\
					test_to_number.c			\
					test_pathname_expansion.c	\
					test_quote_removal.c		\
					test_redirections.c

#==================== OBJECT ====================#

OBJ				:=	$(SRC:%.c=$(BUILD_DIR)%.o)
OBJ_DIR			:=	$(sort $(shell dirname $(OBJ)))

#================== DEPENDENCY ==================#

DEP				:=	$(SRC:%.c=$(BUILD_DIR)%.d)

#==================== COLOR =====================#

INIT			:=	\033[0m
BLACK			:=	\033[30m
RED				:=	\033[31m
GREEN			:=	\033[32m
YELLOW			:=	\033[33m
BLUE			:=	\033[34m
MAGENTA			:=	\033[35m
CYAN			:=	\033[36m

#===================== RULE =====================#
ifndef VERBOSE
.SILENT:
endif

all: display
				if [ ! -f minishell.a ];\
				then $(MAKE) tester -C ../minishell >/dev/null;\
				$(MAKE) fclean -C ../minishell >/dev/null;\
				mv ../minishell/minishell.a minishell.a;\
				fi;
				$(MAKE) $(NAME)
				if [ -f $(NAME) ];\
				then chmod +x $(NAME);\
				valgrind --leak-check=full --show-leak-kinds=all --suppressions=vsupp ./$(NAME);\
				fi;

display:
				clear
				printf "$(BLUE)\n"
				printf "  __  __ _       _     _          _ _    _   _       _ _      _____         _            \n"
				printf " |  \/  (_)_ __ (_)___| |__   ___| | |  | | | |_ __ (_) |_   |_   _|__  ___| |_ ___ _ __ \n"
				printf " | |\/| | | '_ \| / __| '_ \ / _ \ | |  | | | | '_ \| | __|    | |/ _ \/ __| __/ _ \ '__|\n"
				printf " | |  | | | | | | \__ \ | | |  __/ | |  | |_| | | | | | |_     | |  __/\__ \ ||  __/ |   \n"
				printf " |_|  |_|_|_| |_|_|___/_| |_|\___|_|_|   \___/|_| |_|_|\__|    |_|\___||___/\__\___|_|   \n"
				printf "$(INIT)\n"

$(NAME): $(OBJ)
				$(CC) -lreadline $(CFLAGS) -I$(HEADERS) -I$(LIBFT_DIR) $(OBJ) minishell.a -o $(NAME);\
				#printf "$(GREEN)$(NAME) ready ✅️✅️$(INIT)\n";\

$(BUILD_DIR)%.o: %.c | $(OBJ_DIR)
				#printf "$(GREEN)Compiling : $(MAGENTA)$<$(INI\nT)"
				$(CC) $(CFLAGS) -I$(HEADERS) -I$(LIBFT_DIR) -c $< -o $@

$(OBJ_DIR):
				mkdir -p $@

clean:
				if [ -d $(BUILD_DIR) ];\
				then printf "$(RED)Removing directory : $(BLUE)$(BUILD_DIR)$(INIT)\n";\
				rm -rf $(BUILD_DIR);\
				fi;

fclean: clean
				if [ -f minishell.a ];\
				then printf "$(RED)Removing : $(MAGENTA)minishell.a$(INIT)\n";\
				rm -f minishell.a;\
				fi;
				if [ -f cout.log ];\
				then printf "$(RED)Removing : $(MAGENTA)cout.log$(INIT)\n";\
				rm -f cout.log;\
				fi;
				if [ -f cerr.log ];\
				then printf "$(RED)Removing : $(MAGENTA)cerr.log$(INIT)\n";\
				rm -f cerr.log;\
				fi;
				if [ -f $(NAME) ];\
				then printf "$(RED)Removing : $(MAGENTA)$(NAME)$(INIT)\n";\
				rm -f $(NAME);\
				fi;
				$(MAKE) $@ -C ../minishell;\

re: fclean all

.PHONY := all clean fclean re display

-include $(DEP)
