# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/15 14:44:24 by lguerbig          #+#    #+#              #
#    Updated: 2025/01/16 16:49:02 by tle-floc         ###   ########.fr        #
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
SRC				=	minishell.c										\
					tab_utils.c										\
					commands/token.c								\
					commands/ast/execution/common_execution.c		\
					commands/ast/execution/execution.c				\
					commands/ast/execution/operation_execution.c	\
					commands/ast/execution/pipe_execution.c			\
					commands/ast/execution/stack/stack_primitive.c	\
					commands/ast/parsing/parsing.c					\
					commands/ast/parsing/token_state_utils.c		\
					commands/ast/parsing/token_state.c				\
					commands/ast/tree/tree_primitive.c				\
					commands/ast/tree/tree_push.c					\
					commands/builtins/echo.c						\
					commands/builtins/pwd.c							\
					commands/expansion/get_env_var.c				\
					commands/expansion/get_files.c					\
					commands/expansion/pathname_expansion.c			\
					commands/expansion/variable_expansion.c			\
					commands/lexer/format_for_ast.c					\
					commands/lexer/get_token.c						\
					commands/lexer/lexer.c							\
					commands/lexer/token_utils.c					\
					commands/redirection/here_doc.c					\
					commands/redirection/random.c					\
					commands/redirection/redirect.c					\
					commands/redirection/redirection.c				\
					display/display.c								\
					queue/queue_primitive.c							\
					queue/queue_utils.c								\



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

DISPLAY_TRACKER	:=	.display_done

ifndef VERBOSE
.SILENT:
endif

all				:
				$(MAKE) $(NAME) --no-print-directory

$(DISPLAY_TRACKER):
				$(MAKE) display --no-print-directory

display			:
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
				touch $(DISPLAY_TRACKER)
				sleep 0.5

$(LIBFT)		:
				echo "$(BLUE)Making libft👷👷$(INIT)"
				$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(NAME)			:	$(DISPLAY_TRACKER) $(LIBFT) $(OBJ)
				$(CC) -lreadline -I$(HEADERS) -I$(LIBFT_HEADER) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
				echo "$(GREEN)$(NAME) ready ✅️✅️$(INIT)"

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
				rm -f $(DISPLAY_TRACKER)

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
				rm -f $(DISPLAY_TRACKER)

re				:
				rm -f $(DISPLAY_TRACKER)
				$(MAKE) $(DISPLAY_TRACKER) --no-print-directory
				$(MAKE)	fclean --no-print-directory
				touch $(DISPLAY_TRACKER)
				$(MAKE) all --no-print-directory

.PHONY	=	display all clean fclean re $(LIBFT) $(NAME) $(OBJ) $(OBJ_DIR)

-include $(DEP)