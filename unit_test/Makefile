# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/15 14:44:24 by lguerbig          #+#    #+#              #
#    Updated: 2024/12/15 20:21:44 by lguerbig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#===================== BASE =====================#

CC				:=	cc
CFLAGS			+=	-Wall -Wextra -Werror -MP -MMD -g
BUILD_DIR		:=	.build/
LIBFT_DIR		=	../minishell/libft/include
HEADERS			:=	../minishell/include/
NAME			:=	minishell_unit_tester

#==================== SOURCE ====================#

SRC_DIR			=	#src/
SRC				=	unit_test.c\
					test_echo.c

#==================== OBJECT ====================#

OBJ				:=	$(SRC:%.c=$(BUILD_DIR)%.o)
OBJ_DIR			:=	$(sort $(shell dirname $(OBJ)))

#================== DEPENDENCY ==================#

DEP				:=	$(SRC:%.c=$(BUILD_DIR)%.d)

#==================== COLOR =====================#

INIT			:=	\e[0m
BLACK			:=	\e[30m
RED				:=	\e[31m
GREEN			:=	\e[32m
YELLOW			:=	\e[33m
BLUE			:=	\e[34m
MAGENTA			:=	\e[35m
CYAN			:=	\e[36m

#===================== RULE =====================#
ifndef VERBOSE
.SILENT:
endif

all				:	display
				if [ ! -f minishell.a ];\
				then make tester -C ../minishell --no-print-directory;\
				mv ../minishell/minishell.a minishell.a;\
				fi;
				make $(NAME) --no-print-directory
				if [ -f $(NAME) ];\
				then chmod +x $(NAME);\
				./$(NAME);\
				fi;

display			:
				clear
				echo "$(BLUE)  __  __ _       _     _          _ _   _   _       _ _      _____         _            "
				echo " |  \/  (_)_ __ (_)___| |__   ___| | | | | | |_ __ (_) |_   |_   _|__  ___| |_ ___ _ __ "
				echo " | |\/| | | '_ \| / __| '_ \ / _ \ | | | | | | '_ \| | __|    | |/ _ \/ __| __/ _ \ '__|"
				echo " | |  | | | | | | \__ \ | | |  __/ | | | |_| | | | | | |_     | |  __/\__ \ ||  __/ |   "
				echo " |_|  |_|_|_| |_|_|___/_| |_|\___|_|_|  \___/|_| |_|_|\__|    |_|\___||___/\__\___|_|   "
				echo "$(INIT)"
				sleep 0.5

$(NAME)			: $(OBJ)
				cc $(FLAGS) -I$(HEADERS) -I$(LIBFT_DIR) $(OBJ) minishell.a -o $(NAME);\
				#echo "$(GREEN)$(NAME) ready ✅️✅️$(INIT)";\

$(BUILD_DIR)%.o	:	$(SRC_DIR)%.c | $(OBJ_DIR)
				#echo "$(GREEN)Compiling : $(MAGENTA)$<$(INIT)"
				$(CC) $(CFLAGS) -I$(HEADERS) -I$(LIBFT_DIR) -c $< -o $@

$(OBJ_DIR)		:
				mkdir -p $@

clean			:
				if [ -d $(BUILD_DIR) ];\
				then echo "$(RED)Removing directory : $(BLUE)$(BUILD_DIR)$(INIT)";\
				rm -rf $(BUILD_DIR);\
				fi;

fclean			:	clean
				if [ -f minishell.a ];\
				then echo "$(RED)Removing : $(MAGENTA)minishell.a$(INIT)";\
				rm -f minishell.a;\
				fi;
				if [ -f cerr.log ];\
				then echo "$(RED)Removing : $(MAGENTA)cerr.log$(INIT)";\
				rm -f minishell.a;\
				fi;
				if [ -f $(NAME) ];\
				then echo "$(RED)Removing : $(MAGENTA)$(NAME)$(INIT)";\
				rm -f $(NAME);\
				fi;

re:	fclean all

.PHONY	=	all clean fclean re $(NAME) $(OBJ) $(OBJ_DIR)

-include $(DEP)
