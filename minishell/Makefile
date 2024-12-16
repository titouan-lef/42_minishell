# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/15 14:44:24 by lguerbig          #+#    #+#              #
#    Updated: 2024/12/16 21:25:49 by lguerbig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#===================== BASE =====================#

CC				:=	cc
CFLAGS			+=	-Wall -Wextra -Werror -MP -MMD -g
BUILD_DIR		:=	.build/
HEADERS			:=	./include/
NAME			:=	minishell

#==================== SOURCE ====================#

LIBFT_DIR		=	./libft/
LIBFT_HEADER	=	./libft/include
LIBFT			=	$(LIBFT_DIR)libft.a
SRC_DIR			=	./src/
SRC				=	commands/builtins/echo.c

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

all				:
				echo 
				echo " /░░      /░░ /░░           /░░           /░░                 /░░ /░░"
				echo "| ░░░    /░░░|__/          |__/          | ░░                | ░░| ░░"
				echo "| ░░░░  /░░░░ /░░ /░░░░░░░  /░░  /░░░░░░░| ░░░░░░░   /░░░░░░ | ░░| ░░"
				echo "| ░░ ░░/░░ ░░| ░░| ░░__  ░░| ░░ /░░_____/| ░░__  ░░ /░░__  ░░| ░░| ░░"
				echo "| ░░  ░░░| ░░| ░░| ░░  \ ░░| ░░|  ░░░░░░ | ░░  \ ░░| ░░░░░░░░| ░░| ░░"
				echo "| ░░\  ░ | ░░| ░░| ░░  | ░░| ░░ \____  ░░| ░░  | ░░| ░░_____/| ░░| ░░"
				echo "| ░░ \/  | ░░| ░░| ░░  | ░░| ░░ /░░░░░░░/| ░░  | ░░|  ░░░░░░░| ░░| ░░"
				echo "|__/     |__/|__/|__/  |__/|__/|_______/ |__/  |__/ \_______/|__/|__/"
				echo 
				sleep 0.5
				$(MAKE) $(NAME) --no-print-directory

$(LIBFT)		:
				echo "$(BLUE)Making libft👷👷$(INIT)"
				$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(NAME)			:	$(LIBFT) $(OBJ)
				cc  -I$(HEADERS) -I$(LIBFT_HEADER) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME);\
				echo "$(GREEN)$(NAME) ready ✅️✅️$(INIT)";\

$(BUILD_DIR)%.o	:	$(SRC_DIR)%.c | $(OBJ_DIR)
				echo "$(GREEN)Compiling : $(MAGENTA)$<$(INIT)"
				$(CC) -I$(HEADERS) -I$(LIBFT_HEADER) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)		:
				mkdir -p $@

tester			:	$(LIBFT) $(filter-out minishell.c ,$(OBJ))
				cp $(LIBFT) $(NAME).a
				ar -rs $(NAME).a $(filter-out minishell.c ,$(OBJ))
				echo "$(GREEN)$(NAME).a ready for tester ✅️✅️$(INIT)";\

clean			:
				if [ -d $(LIBFT_DIR)$(BUILD_DIR) ];\
				then echo "$(BLUE)Cleanning libft✨🧹$(INIT)";\
				$(MAKE) $@ -C $(LIBFT_DIR) --no-print-directory;\
				fi;
				if [ -d $(BUILD_DIR) ];\
				then echo "$(BLUE)Cleanning $(NAME)✨🧹$(INIT)";\
				echo "$(RED)Removing directory : $(BLUE)$(BUILD_DIR)$(INIT)";\
				rm -rf $(BUILD_DIR);\
				fi;

fclean			:	clean
				if [ -f $(LIBFT) ];\
				then echo "$(BLUE)Cleanning libft✨🧹$(INIT)";\
				$(MAKE) $@ -C $(LIBFT_DIR) --no-print-directory;\
				fi;
				if [ -f $(NAME) ];\
				then echo "$(BLUE)Cleanning $(NAME)✨🧹$(INIT)";\
				echo "$(RED)Removing : $(MAGENTA)$(NAME)$(INIT)";\
				rm -f $(NAME);\
				fi;

re:	fclean all

.PHONY	=	all clean fclean re $(LIBFT) $(NAME) $(OBJ) $(OBJ_DIR)

-include $(DEP)
